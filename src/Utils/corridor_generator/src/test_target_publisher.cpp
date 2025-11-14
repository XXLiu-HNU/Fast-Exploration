#include <ros/ros.h>
#include <onboard_detector/TargetBox3D.h>
#include <onboard_detector/TargetBoxArray.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

class TestTargetPublisher
{
public:
    TestTargetPublisher() : nh_("~")
    {
        // 发布目标检测结果
        target_pub_ = nh_.advertise<onboard_detector::TargetBoxArray>("/detector/target_boxes", 10);
        
        // 发布可视化标记
        marker_pub_ = nh_.advertise<visualization_msgs::MarkerArray>("/test_target/markers", 10);
        
        // 参数
        nh_.param("publish_rate", publish_rate_, 1.0);
        nh_.param("target_x", target_x_, 5.0);
        nh_.param("target_y", target_y_, 0.0);
        nh_.param("target_z", target_z_, 1.0);
        nh_.param("target_size_x", target_size_x_, 1.0);
        nh_.param("target_size_y", target_size_y_, 1.0);
        nh_.param("target_size_z", target_size_z_, 1.0);
        
        ROS_INFO("[TestTargetPublisher] Initialized!");
        ROS_INFO("[TestTargetPublisher] Publishing target at [%.2f, %.2f, %.2f] with size [%.2f, %.2f, %.2f]",
                 target_x_, target_y_, target_z_, 
                 target_size_x_, target_size_y_, target_size_z_);
        ROS_INFO("[TestTargetPublisher] Publishing rate: %.2f Hz", publish_rate_);
    }
    
    void run()
    {
        ros::Rate rate(publish_rate_);
        
        while (ros::ok())
        {
            publishTarget();
            publishMarkers();
            
            ros::spinOnce();
            rate.sleep();
        }
    }
    
private:
    void publishTarget()
    {
        onboard_detector::TargetBoxArray target_array;
        target_array.header.stamp = ros::Time::now();
        target_array.header.frame_id = "world";
        
        onboard_detector::TargetBox3D target;
        target.x = target_x_;
        target.y = target_y_;
        target.z = target_z_;
        target.x_width = target_size_x_;
        target.y_width = target_size_y_;
        target.z_width = target_size_z_;
        target.id = 1.0;
        
        target_array.targets.push_back(target);
        
        target_pub_.publish(target_array);
        
        ROS_INFO_THROTTLE(5.0, "[TestTargetPublisher] Publishing target box");
    }
    
    void publishMarkers()
    {
        visualization_msgs::MarkerArray marker_array;
        
        // 创建3D框标记
        visualization_msgs::Marker box_marker;
        box_marker.header.frame_id = "world";
        box_marker.header.stamp = ros::Time::now();
        box_marker.ns = "test_target_box";
        box_marker.id = 0;
        box_marker.type = visualization_msgs::Marker::CUBE;
        box_marker.action = visualization_msgs::Marker::ADD;
        
        box_marker.pose.position.x = target_x_;
        box_marker.pose.position.y = target_y_;
        box_marker.pose.position.z = target_z_;
        box_marker.pose.orientation.x = 0.0;
        box_marker.pose.orientation.y = 0.0;
        box_marker.pose.orientation.z = 0.0;
        box_marker.pose.orientation.w = 1.0;
        
        box_marker.scale.x = target_size_x_;
        box_marker.scale.y = target_size_y_;
        box_marker.scale.z = target_size_z_;
        
        box_marker.color.r = 1.0;
        box_marker.color.g = 0.5;
        box_marker.color.b = 0.0;
        box_marker.color.a = 0.5;
        
        marker_array.markers.push_back(box_marker);
        
        // 创建标签
        visualization_msgs::Marker text_marker;
        text_marker.header.frame_id = "world";
        text_marker.header.stamp = ros::Time::now();
        text_marker.ns = "test_target_label";
        text_marker.id = 1;
        text_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
        text_marker.action = visualization_msgs::Marker::ADD;
        
        text_marker.pose.position.x = target_x_;
        text_marker.pose.position.y = target_y_;
        text_marker.pose.position.z = target_z_ + target_size_z_ / 2.0 + 0.5;
        text_marker.pose.orientation.w = 1.0;
        
        text_marker.scale.z = 0.5;
        
        text_marker.color.r = 1.0;
        text_marker.color.g = 1.0;
        text_marker.color.b = 1.0;
        text_marker.color.a = 1.0;
        
        text_marker.text = "TEST TARGET";
        
        marker_array.markers.push_back(text_marker);
        
        marker_pub_.publish(marker_array);
    }

private:
    ros::NodeHandle nh_;
    ros::Publisher target_pub_;
    ros::Publisher marker_pub_;
    
    double publish_rate_;
    double target_x_;
    double target_y_;
    double target_z_;
    double target_size_x_;
    double target_size_y_;
    double target_size_z_;
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "test_target_publisher");
    
    TestTargetPublisher publisher;
    publisher.run();
    
    return 0;
}

