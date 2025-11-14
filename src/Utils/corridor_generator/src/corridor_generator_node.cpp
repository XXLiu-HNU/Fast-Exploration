#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Point.h>
#include <sensor_msgs/PointCloud2.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <decomp_ros_msgs/Polyhedron.h>
#include <decomp_ros_msgs/PolyhedronArray.h>
#include <nav_msgs/Odometry.h>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/extract_indices.h>

#include <Eigen/Eigen>
#include <vector>
#include <map>
#include <set>

// Include DecompROS headers
#include <decomp_basis/data_type.h>
#include <decomp_util/seed_decomp.h>
#include <decomp_ros_utils/data_ros_utils.h>

// Include LV-DOT target detection messages
#include <onboard_detector/TargetBox3D.h>
#include <onboard_detector/TargetBoxArray.h>

// 走廊信息结构体
struct CorridorInfo {
    int target_id;              // 目标ID
    Vec3f seed_point;           // 种子点位置
    Polyhedron3D polyhedron;    // 多面体走廊
    ros::Time last_update;      // 最后更新时间
    onboard_detector::TargetBox3D target_box;  // 目标框信息（用于点云处理）
};

class CorridorGenerator
{
public:
    CorridorGenerator() : nh_("~")
    {
        // 订阅 RViz 中的点击位置（手动模式）
        clicked_point_sub_ = nh_.subscribe("/clicked_point", 10, &CorridorGenerator::clickedPointCallback, this);
        
        // 订阅目标检测结果（自动模式）
        // LV-DOT 发布到 /onboard_detector/confirmed_targets
        target_box_sub_ = nh_.subscribe("/onboard_detector/confirmed_targets", 10, &CorridorGenerator::targetBoxCallback, this);
        
        // 订阅障碍物点云（可以从不同的源订阅）
        obstacle_cloud_sub_ = nh_.subscribe("/map_ros/cloud", 10, &CorridorGenerator::obstacleCloudCallback, this);
        
        // 发布飞行走廊可视化
        corridor_pub_ = nh_.advertise<decomp_ros_msgs::PolyhedronArray>("/corridor_generator/polyhedrons", 10);
        corridor_marker_pub_ = nh_.advertise<visualization_msgs::MarkerArray>("/corridor_generator/markers", 10);
        
        // 发布处理后的点云（用于调试）
        processed_cloud_pub_ = nh_.advertise<sensor_msgs::PointCloud2>("/corridor_generator/processed_cloud", 10);
        
        // 参数
        nh_.param("corridor_radius", corridor_radius_, 2.0);
        nh_.param("local_bbox_x", local_bbox_x_, 5.0);
        nh_.param("local_bbox_y", local_bbox_y_, 5.0);
        nh_.param("local_bbox_z", local_bbox_z_, 3.0);
        nh_.param("obstacle_search_radius", obstacle_search_radius_, 10.0);
        nh_.param("min_ground_height", min_ground_height_, 0.0);  // 最小地面高度
        nh_.param("target_bbox_padding", target_bbox_padding_, 0.5);  // 目标框膨胀量，用于安全裕度
        
        ROS_INFO("[CorridorGenerator] Node initialized!");
        ROS_INFO("[CorridorGenerator] Support both manual (click) and automatic (target detection) mode");
        ROS_INFO("[CorridorGenerator] Parameters: radius=%.2f, bbox=[%.2f, %.2f, %.2f], min_height=%.2f, bbox_padding=%.2f", 
                 corridor_radius_, local_bbox_x_, local_bbox_y_, local_bbox_z_, min_ground_height_, target_bbox_padding_);
    }

private:
    void clickedPointCallback(const geometry_msgs::PointStampedConstPtr& msg)
    {
        ROS_INFO("[CorridorGenerator] [Manual Mode] Received clicked point: [%.2f, %.2f, %.2f]",
                 msg->point.x, msg->point.y, msg->point.z);
        
        if (obstacle_cloud_.empty())
        {
            ROS_WARN_THROTTLE(5.0, "[CorridorGenerator] No obstacle cloud received yet!");
            return;
        }
        
        // 提取点击位置附近的障碍物
        Vec3f seed_point(msg->point.x, msg->point.y, msg->point.z);
        vec_Vec3f local_obstacles = extractLocalObstacles(seed_point);
        
        ROS_INFO("[CorridorGenerator] Found %lu local obstacles", local_obstacles.size());
        
        // 使用 SeedDecomp 生成飞行走廊
        generateCorridor(seed_point, local_obstacles);
    }
    
    void targetBoxCallback(const onboard_detector::TargetBoxArrayConstPtr& msg)
    {
        // 只在有目标时打印INFO，没有目标时使用DEBUG级别（低频率）
        if (msg->targets.size() > 0)
        {
            ROS_INFO("[CorridorGenerator] [Auto Mode] Received %lu target(s)", msg->targets.size());
        }
        else
        {
            ROS_DEBUG_THROTTLE(10.0, "[CorridorGenerator] [Auto Mode] Received 0 targets");
        }
        
        if (obstacle_cloud_.empty())
        {
            ROS_WARN_THROTTLE(5.0, "[CorridorGenerator] No obstacle cloud received yet!");
            return;
        }
        
        // 收集当前消息中的所有目标ID
        std::set<int> current_target_ids;
        
        // 处理每个检测到的目标
        for (size_t i = 0; i < msg->targets.size(); i++)
        {
            const auto& target = msg->targets[i];
            int target_id = static_cast<int>(target.id);
            current_target_ids.insert(target_id);
            
            // 检查是否是新目标或需要更新
            bool is_new_target = (target_corridors_.find(target_id) == target_corridors_.end());
            
            if (is_new_target)
            {
                ROS_INFO("[CorridorGenerator] NEW target ID=%d: pos=[%.2f, %.2f, %.2f], size=[%.2f, %.2f, %.2f]",
                         target_id, target.x, target.y, target.z, 
                         target.x_width, target.y_width, target.z_width);
            }
            else
            {
                // 检查位置是否有显著变化（大于阈值才更新）
                Vec3f old_pos = target_corridors_[target_id].seed_point;
                Vec3f new_pos(target.x, target.y, target.z);
                double position_change = (new_pos - old_pos).norm();
                
                if (position_change < 0.3)  // 位置变化小于0.3米，跳过更新
                {
                    ROS_DEBUG("[CorridorGenerator] Target ID=%d position change %.2fm < 0.3m, skipping update",
                             target_id, position_change);
                    target_corridors_[target_id].last_update = ros::Time::now();
                    continue;
                }
                
                ROS_INFO("[CorridorGenerator] UPDATE target ID=%d: pos change=%.2fm, new pos=[%.2f, %.2f, %.2f]",
                         target_id, position_change, target.x, target.y, target.z);
            }
            
            // 1. 从障碍物点云中移除目标区域（带有padding）
            pcl::PointCloud<pcl::PointXYZ> processed_cloud = 
                removeTargetFromCloud(obstacle_cloud_, target);
            
            // 2. 提取目标位置附近的障碍物（从处理后的点云）
            Vec3f seed_point(target.x, target.y, target.z);
            vec_Vec3f local_obstacles = extractLocalObstacles(seed_point, processed_cloud);
            
            ROS_INFO("[CorridorGenerator] Target ID=%d: Found %lu local obstacles (after removing target)", 
                     target_id, local_obstacles.size());
            
            // 3. 生成或更新飞行走廊
            Polyhedron3D polyhedron = generateCorridorForTarget(seed_point, local_obstacles);
            
            // 4. 保存或更新走廊信息
            CorridorInfo corridor_info;
            corridor_info.target_id = target_id;
            corridor_info.seed_point = seed_point;
            corridor_info.polyhedron = polyhedron;
            corridor_info.last_update = ros::Time::now();
            corridor_info.target_box = target;
            
            target_corridors_[target_id] = corridor_info;
        }
        
        // 删除已消失的目标对应的走廊
        auto it = target_corridors_.begin();
        while (it != target_corridors_.end())
        {
            if (current_target_ids.find(it->first) == current_target_ids.end())
            {
                ROS_INFO("[CorridorGenerator] REMOVE disappeared target ID=%d", it->first);
                it = target_corridors_.erase(it);
            }
            else
            {
                ++it;
            }
        }
        
        // 发布所有走廊
        publishAllCorridors();
        
        ROS_INFO_THROTTLE(2.0, "[CorridorGenerator] Current active corridors: %lu (matching %lu targets)", 
                          target_corridors_.size(), msg->targets.size());
    }
    
    void obstacleCloudCallback(const sensor_msgs::PointCloud2ConstPtr& msg)
    {
        // 将 ROS 点云转换为 PCL 点云
        pcl::fromROSMsg(*msg, obstacle_cloud_);
        // ROS_INFO_THROTTLE(5.0, "[CorridorGenerator] Received obstacle cloud with %lu points", 
        //                   obstacle_cloud_.points.size());
    }
    
    // 从默认障碍物点云提取局部障碍物
    vec_Vec3f extractLocalObstacles(const Vec3f& center)
    {
        return extractLocalObstacles(center, obstacle_cloud_);
    }
    
    // 从指定点云提取局部障碍物（重载版本）
    vec_Vec3f extractLocalObstacles(const Vec3f& center, 
                                     const pcl::PointCloud<pcl::PointXYZ>& cloud)
    {
        vec_Vec3f local_obs;
        double search_radius_sq = obstacle_search_radius_ * obstacle_search_radius_;
        
        for (const auto& pt : cloud.points)
        {
            Vec3f obs_pt(pt.x, pt.y, pt.z);
            double dist_sq = (obs_pt - center).squaredNorm();
            
            if (dist_sq < search_radius_sq)
            {
                local_obs.push_back(obs_pt);
            }
        }
        
        return local_obs;
    }
    
    // 从点云中移除目标3D框内的点（关键函数：处理目标点云）
    pcl::PointCloud<pcl::PointXYZ> removeTargetFromCloud(
        const pcl::PointCloud<pcl::PointXYZ>& input_cloud,
        const onboard_detector::TargetBox3D& target)
    {
        pcl::PointCloud<pcl::PointXYZ> output_cloud;
        
        // 计算膨胀后的边界框
        double half_x = (target.x_width / 2.0) + target_bbox_padding_;
        double half_y = (target.y_width / 2.0) + target_bbox_padding_;
        double half_z = (target.z_width / 2.0) + target_bbox_padding_;
        
        // 边界框的最小和最大坐标
        double min_x = target.x - half_x;
        double max_x = target.x + half_x;
        double min_y = target.y - half_y;
        double max_y = target.y + half_y;
        double min_z = target.z - half_z;
        double max_z = target.z + half_z;
        
        ROS_DEBUG("[CorridorGenerator] Removing points in bbox: [%.2f,%.2f] x [%.2f,%.2f] x [%.2f,%.2f]",
                  min_x, max_x, min_y, max_y, min_z, max_z);
        
        int removed_count = 0;
        
        // 遍历所有点，保留不在目标框内的点
        for (const auto& pt : input_cloud.points)
        {
            // 检查点是否在膨胀后的边界框内
            if (pt.x >= min_x && pt.x <= max_x &&
                pt.y >= min_y && pt.y <= max_y &&
                pt.z >= min_z && pt.z <= max_z)
            {
                // 点在目标框内，跳过（移除）
                removed_count++;
                continue;
            }
            
            // 点在目标框外，保留
            output_cloud.points.push_back(pt);
        }
        
        output_cloud.width = output_cloud.points.size();
        output_cloud.height = 1;
        output_cloud.is_dense = true;
        
        ROS_DEBUG("[CorridorGenerator] Removed %d points from cloud (original: %lu -> processed: %lu)",
                  removed_count, input_cloud.points.size(), output_cloud.points.size());
        
        return output_cloud;
    }
    
    // 发布处理后的点云（用于调试可视化）
    void publishProcessedCloud(const pcl::PointCloud<pcl::PointXYZ>& cloud)
    {
        sensor_msgs::PointCloud2 cloud_msg;
        pcl::toROSMsg(cloud, cloud_msg);
        cloud_msg.header.frame_id = "world";
        cloud_msg.header.stamp = ros::Time::now();
        processed_cloud_pub_.publish(cloud_msg);
    }
    
    void generateCorridor(const Vec3f& seed_point, const vec_Vec3f& obstacles)
    {
        Polyhedron3D polyhedron = generateCorridorForTarget(seed_point, obstacles);
        // 发布可视化（用于手动模式）
        publishCorridor(seed_point, polyhedron);
    }
    
    // 为目标生成走廊（返回多面体，不直接发布）
    Polyhedron3D generateCorridorForTarget(const Vec3f& seed_point, const vec_Vec3f& obstacles)
    {
        // 创建 SeedDecomp3D 对象
        SeedDecomp3D decomp(seed_point);
        
        // 设置障碍物
        decomp.set_obs(obstacles);
        
        // 设置局部边界框
        Vec3f local_bbox(local_bbox_x_, local_bbox_y_, local_bbox_z_);
        decomp.set_local_bbox(local_bbox);
        
        // 执行膨胀，生成飞行走廊
        decomp.dilate(corridor_radius_);
        
        // 获取多面体
        Polyhedron3D polyhedron = decomp.get_polyhedron();
        
        // 添加地面约束：限制 Z >= min_ground_height_
        // 创建地面平面 (法向量 = [0, 0, -1] 指向不可行域（地下），点在 z=min_ground_height_)
        Vec3f ground_point(0.0, 0.0, min_ground_height_);  // 地面上的一个点
        Vec3f ground_normal(0.0, 0.0, -1.0); // 法向量向下（指向地下不可行域）
        Hyperplane3D ground_plane(ground_point, ground_normal);
        polyhedron.add(ground_plane);
        
        ROS_DEBUG("[CorridorGenerator] Generated corridor with %lu hyperplanes (including ground constraint)", 
                  polyhedron.hyperplanes().size());
        
        return polyhedron;
    }
    
    // 发布所有目标的走廊
    void publishAllCorridors()
    {
        if (target_corridors_.empty())
        {
            ROS_DEBUG("[CorridorGenerator] No corridors to publish");
            return;
        }
        
        // 发布 PolyhedronArray 消息（包含所有走廊）
        decomp_ros_msgs::PolyhedronArray poly_array_msg;
        poly_array_msg.header.frame_id = "world";
        poly_array_msg.header.stamp = ros::Time::now();
        
        // 发布 Marker 可视化
        visualization_msgs::MarkerArray marker_array;
        int marker_id = 0;
        
        for (const auto& pair : target_corridors_)
        {
            const CorridorInfo& corridor = pair.second;
            
            // 添加多面体到数组
            decomp_ros_msgs::Polyhedron poly_msg;
            const auto& hyperplanes = corridor.polyhedron.hyperplanes();
            
            for (const auto& hp : hyperplanes)
            {
                geometry_msgs::Point pt_msg, normal_msg;
                pt_msg.x = hp.p_(0);
                pt_msg.y = hp.p_(1);
                pt_msg.z = hp.p_(2);
                normal_msg.x = hp.n_(0);
                normal_msg.y = hp.n_(1);
                normal_msg.z = hp.n_(2);
                
                poly_msg.points.push_back(pt_msg);
                poly_msg.normals.push_back(normal_msg);
            }
            
            poly_array_msg.polyhedrons.push_back(poly_msg);
            
            // 创建可视化标记
            // 1. 中心点标记
            visualization_msgs::Marker center_marker;
            center_marker.header.frame_id = "world";
            center_marker.header.stamp = ros::Time::now();
            center_marker.ns = "corridor_centers";
            center_marker.id = marker_id++;
            center_marker.type = visualization_msgs::Marker::SPHERE;
            center_marker.action = visualization_msgs::Marker::ADD;
            center_marker.pose.position.x = corridor.seed_point(0);
            center_marker.pose.position.y = corridor.seed_point(1);
            center_marker.pose.position.z = corridor.seed_point(2);
            center_marker.pose.orientation.w = 1.0;
            center_marker.scale.x = 0.3;
            center_marker.scale.y = 0.3;
            center_marker.scale.z = 0.3;
            center_marker.color.r = 1.0;
            center_marker.color.g = 0.0;
            center_marker.color.b = 0.0;
            center_marker.color.a = 1.0;
            marker_array.markers.push_back(center_marker);
            
            // 2. 目标ID文本标记
            visualization_msgs::Marker text_marker;
            text_marker.header.frame_id = "world";
            text_marker.header.stamp = ros::Time::now();
            text_marker.ns = "corridor_labels";
            text_marker.id = marker_id++;
            text_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
            text_marker.action = visualization_msgs::Marker::ADD;
            text_marker.pose.position.x = corridor.seed_point(0);
            text_marker.pose.position.y = corridor.seed_point(1);
            text_marker.pose.position.z = corridor.seed_point(2) + 1.5;
            text_marker.pose.orientation.w = 1.0;
            text_marker.scale.z = 0.5;
            text_marker.color.r = 1.0;
            text_marker.color.g = 1.0;
            text_marker.color.b = 0.0;
            text_marker.color.a = 1.0;
            text_marker.text = "Target " + std::to_string(corridor.target_id);
            marker_array.markers.push_back(text_marker);
            
            // 3. 多面体边界平面标记
            for (const auto& hp : hyperplanes)
            {
                visualization_msgs::Marker plane_marker;
                plane_marker.header.frame_id = "world";
                plane_marker.header.stamp = ros::Time::now();
                plane_marker.ns = "corridor_planes";
                plane_marker.id = marker_id++;
                plane_marker.type = visualization_msgs::Marker::ARROW;
                plane_marker.action = visualization_msgs::Marker::ADD;
                
                // 箭头起点（平面上的点）
                plane_marker.points.resize(2);
                plane_marker.points[0].x = hp.p_(0);
                plane_marker.points[0].y = hp.p_(1);
                plane_marker.points[0].z = hp.p_(2);
                
                // 箭头终点（沿法向量方向）
                plane_marker.points[1].x = hp.p_(0) + hp.n_(0) * 0.5;
                plane_marker.points[1].y = hp.p_(1) + hp.n_(1) * 0.5;
                plane_marker.points[1].z = hp.p_(2) + hp.n_(2) * 0.5;
                
                plane_marker.scale.x = 0.05;  // 箭头杆直径
                plane_marker.scale.y = 0.1;   // 箭头头直径
                plane_marker.color.r = 0.0;
                plane_marker.color.g = 1.0;
                plane_marker.color.b = 0.0;
                plane_marker.color.a = 0.6;
                
                marker_array.markers.push_back(plane_marker);
            }
        }
        
        corridor_pub_.publish(poly_array_msg);
        corridor_marker_pub_.publish(marker_array);
        
        ROS_DEBUG("[CorridorGenerator] Published %lu corridors", target_corridors_.size());
    }
    
    void publishCorridor(const Vec3f& seed_point, const Polyhedron3D& polyhedron)
    {
        // 发布 PolyhedronArray 消息
        decomp_ros_msgs::PolyhedronArray poly_array_msg;
        poly_array_msg.header.frame_id = "world";
        poly_array_msg.header.stamp = ros::Time::now();
        
        decomp_ros_msgs::Polyhedron poly_msg;
        const auto& hyperplanes = polyhedron.hyperplanes();
        
        for (const auto& hp : hyperplanes)
        {
            geometry_msgs::Point pt_msg, normal_msg;
            pt_msg.x = hp.p_(0);
            pt_msg.y = hp.p_(1);
            pt_msg.z = hp.p_(2);
            normal_msg.x = hp.n_(0);
            normal_msg.y = hp.n_(1);
            normal_msg.z = hp.n_(2);
            
            poly_msg.points.push_back(pt_msg);
            poly_msg.normals.push_back(normal_msg);
        }
        
        poly_array_msg.polyhedrons.push_back(poly_msg);
        corridor_pub_.publish(poly_array_msg);
        
        // 发布 Marker 可视化
        publishMarkers(seed_point, polyhedron);
    }
    
    void publishMarkers(const Vec3f& seed_point, const Polyhedron3D& polyhedron)
    {
        visualization_msgs::MarkerArray marker_array;
        
        // 创建中心点标记
        visualization_msgs::Marker center_marker;
        center_marker.header.frame_id = "world";
        center_marker.header.stamp = ros::Time::now();
        center_marker.ns = "corridor_center";
        center_marker.id = 0;
        center_marker.type = visualization_msgs::Marker::SPHERE;
        center_marker.action = visualization_msgs::Marker::ADD;
        center_marker.pose.position.x = seed_point(0);
        center_marker.pose.position.y = seed_point(1);
        center_marker.pose.position.z = seed_point(2);
        center_marker.pose.orientation.w = 1.0;
        center_marker.scale.x = 0.3;
        center_marker.scale.y = 0.3;
        center_marker.scale.z = 0.3;
        center_marker.color.r = 1.0;
        center_marker.color.g = 0.0;
        center_marker.color.b = 0.0;
        center_marker.color.a = 1.0;
        marker_array.markers.push_back(center_marker);
        
        // 创建多面体边界标记
        const auto& hyperplanes = polyhedron.hyperplanes();
        int id = 1;
        
        for (const auto& hp : hyperplanes)
        {
            visualization_msgs::Marker plane_marker;
            plane_marker.header.frame_id = "world";
            plane_marker.header.stamp = ros::Time::now();
            plane_marker.ns = "corridor_planes";
            plane_marker.id = id++;
            plane_marker.type = visualization_msgs::Marker::ARROW;
            plane_marker.action = visualization_msgs::Marker::ADD;
            
            // 箭头起点（平面上的点）
            plane_marker.points.resize(2);
            plane_marker.points[0].x = hp.p_(0);
            plane_marker.points[0].y = hp.p_(1);
            plane_marker.points[0].z = hp.p_(2);
            
            // 箭头终点（沿法向量方向）
            plane_marker.points[1].x = hp.p_(0) + hp.n_(0) * 0.5;
            plane_marker.points[1].y = hp.p_(1) + hp.n_(1) * 0.5;
            plane_marker.points[1].z = hp.p_(2) + hp.n_(2) * 0.5;
            
            plane_marker.scale.x = 0.05;  // 箭头杆直径
            plane_marker.scale.y = 0.1;   // 箭头头直径
            plane_marker.color.r = 0.0;
            plane_marker.color.g = 1.0;
            plane_marker.color.b = 0.0;
            plane_marker.color.a = 0.6;
            
            marker_array.markers.push_back(plane_marker);
        }
        
        // 创建边界框线框
        visualization_msgs::Marker bbox_marker;
        bbox_marker.header.frame_id = "world";
        bbox_marker.header.stamp = ros::Time::now();
        bbox_marker.ns = "corridor_bbox";
        bbox_marker.id = id++;
        bbox_marker.type = visualization_msgs::Marker::LINE_LIST;
        bbox_marker.action = visualization_msgs::Marker::ADD;
        bbox_marker.scale.x = 0.05;
        bbox_marker.color.r = 0.0;
        bbox_marker.color.g = 0.5;
        bbox_marker.color.b = 1.0;
        bbox_marker.color.a = 0.8;
        
        // 绘制边界框的12条边
        double hx = local_bbox_x_;
        double hy = local_bbox_y_;
        double hz = local_bbox_z_;
        Vec3f corners[8] = {
            seed_point + Vec3f(-hx, -hy, -hz),
            seed_point + Vec3f( hx, -hy, -hz),
            seed_point + Vec3f( hx,  hy, -hz),
            seed_point + Vec3f(-hx,  hy, -hz),
            seed_point + Vec3f(-hx, -hy,  hz),
            seed_point + Vec3f( hx, -hy,  hz),
            seed_point + Vec3f( hx,  hy,  hz),
            seed_point + Vec3f(-hx,  hy,  hz)
        };
        
        // 底面4条边
        int edges[12][2] = {
            {0,1}, {1,2}, {2,3}, {3,0},  // 底面
            {4,5}, {5,6}, {6,7}, {7,4},  // 顶面
            {0,4}, {1,5}, {2,6}, {3,7}   // 竖边
        };
        
        for (int i = 0; i < 12; i++)
        {
            geometry_msgs::Point p1, p2;
            p1.x = corners[edges[i][0]](0);
            p1.y = corners[edges[i][0]](1);
            p1.z = corners[edges[i][0]](2);
            p2.x = corners[edges[i][1]](0);
            p2.y = corners[edges[i][1]](1);
            p2.z = corners[edges[i][1]](2);
            bbox_marker.points.push_back(p1);
            bbox_marker.points.push_back(p2);
        }
        
        marker_array.markers.push_back(bbox_marker);
        
        corridor_marker_pub_.publish(marker_array);
        
        ROS_INFO("[CorridorGenerator] Published corridor visualization");
    }

private:
    ros::NodeHandle nh_;
    
    // 订阅者
    ros::Subscriber clicked_point_sub_;      // 手动点击模式
    ros::Subscriber target_box_sub_;         // 自动目标检测模式
    ros::Subscriber obstacle_cloud_sub_;     // 障碍物点云
    
    // 发布者
    ros::Publisher corridor_pub_;            // 走廊多面体
    ros::Publisher corridor_marker_pub_;     // 走廊可视化标记
    ros::Publisher processed_cloud_pub_;     // 处理后的点云（调试用）
    
    // 数据
    pcl::PointCloud<pcl::PointXYZ> obstacle_cloud_;
    std::map<int, CorridorInfo> target_corridors_;  // 目标ID -> 走廊信息的映射
    
    // 参数
    double corridor_radius_;
    double local_bbox_x_;
    double local_bbox_y_;
    double local_bbox_z_;
    double obstacle_search_radius_;
    double min_ground_height_;      // 最小地面高度，限制飞行走廊不低于此高度
    double target_bbox_padding_;    // 目标框膨胀量，用于安全裕度
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "corridor_generator_node");
    
    CorridorGenerator generator;
    
    ros::spin();
    
    return 0;
}

