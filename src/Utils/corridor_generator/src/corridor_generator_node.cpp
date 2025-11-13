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

#include <Eigen/Eigen>
#include <vector>

// Include DecompROS headers
#include <decomp_basis/data_type.h>
#include <decomp_util/seed_decomp.h>
#include <decomp_ros_utils/data_ros_utils.h>

class CorridorGenerator
{
public:
    CorridorGenerator() : nh_("~")
    {
        // 订阅 RViz 中的点击位置
        clicked_point_sub_ = nh_.subscribe("/clicked_point", 10, &CorridorGenerator::clickedPointCallback, this);
        
        // 订阅障碍物点云（可以从不同的源订阅）
        obstacle_cloud_sub_ = nh_.subscribe("/map_ros/cloud", 10, &CorridorGenerator::obstacleCloudCallback, this);
        
        // 发布飞行走廊可视化
        corridor_pub_ = nh_.advertise<decomp_ros_msgs::PolyhedronArray>("/corridor_generator/polyhedrons", 10);
        corridor_marker_pub_ = nh_.advertise<visualization_msgs::MarkerArray>("/corridor_generator/markers", 10);
        
        // 参数
        nh_.param("corridor_radius", corridor_radius_, 2.0);
        nh_.param("local_bbox_x", local_bbox_x_, 5.0);
        nh_.param("local_bbox_y", local_bbox_y_, 5.0);
        nh_.param("local_bbox_z", local_bbox_z_, 3.0);
        nh_.param("obstacle_search_radius", obstacle_search_radius_, 10.0);
        
        ROS_INFO("[CorridorGenerator] Node initialized!");
        ROS_INFO("[CorridorGenerator] Click points in RViz using 'Publish Point' tool");
        ROS_INFO("[CorridorGenerator] Parameters: radius=%.2f, bbox=[%.2f, %.2f, %.2f]", 
                 corridor_radius_, local_bbox_x_, local_bbox_y_, local_bbox_z_);
    }

private:
    void clickedPointCallback(const geometry_msgs::PointStampedConstPtr& msg)
    {
        ROS_INFO("[CorridorGenerator] Received clicked point: [%.2f, %.2f, %.2f]",
                 msg->point.x, msg->point.y, msg->point.z);
        
        if (obstacle_cloud_.empty())
        {
            ROS_WARN("[CorridorGenerator] No obstacle cloud received yet!");
            return;
        }
        
        // 提取点击位置附近的障碍物
        Vec3f seed_point(msg->point.x, msg->point.y, msg->point.z);
        vec_Vec3f local_obstacles = extractLocalObstacles(seed_point);
        
        ROS_INFO("[CorridorGenerator] Found %lu local obstacles", local_obstacles.size());
        
        // 使用 SeedDecomp 生成飞行走廊
        generateCorridor(seed_point, local_obstacles);
    }
    
    void obstacleCloudCallback(const sensor_msgs::PointCloud2ConstPtr& msg)
    {
        // 将 ROS 点云转换为 PCL 点云
        pcl::fromROSMsg(*msg, obstacle_cloud_);
        // ROS_INFO_THROTTLE(5.0, "[CorridorGenerator] Received obstacle cloud with %lu points", 
        //                   obstacle_cloud_.points.size());
    }
    
    vec_Vec3f extractLocalObstacles(const Vec3f& center)
    {
        vec_Vec3f local_obs;
        double search_radius_sq = obstacle_search_radius_ * obstacle_search_radius_;
        
        for (const auto& pt : obstacle_cloud_.points)
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
    
    void generateCorridor(const Vec3f& seed_point, const vec_Vec3f& obstacles)
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
        
        ROS_INFO("[CorridorGenerator] Generated corridor with %lu hyperplanes", 
                 polyhedron.hyperplanes().size());
        
        // 发布可视化
        publishCorridor(seed_point, polyhedron);
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
    ros::Subscriber clicked_point_sub_;
    ros::Subscriber obstacle_cloud_sub_;
    ros::Publisher corridor_pub_;
    ros::Publisher corridor_marker_pub_;
    
    pcl::PointCloud<pcl::PointXYZ> obstacle_cloud_;
    
    double corridor_radius_;
    double local_bbox_x_;
    double local_bbox_y_;
    double local_bbox_z_;
    double obstacle_search_radius_;
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "corridor_generator_node");
    
    CorridorGenerator generator;
    
    ros::spin();
    
    return 0;
}

