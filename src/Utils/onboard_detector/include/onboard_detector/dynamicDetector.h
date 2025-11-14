/*
    FILE: dynamicDetector.h
    ---------------------------------
    header file of dynamic obstacle detector
*/
#ifndef ONBOARDDETECTOR_DYNAMICDETECTOR_H
#define ONBOARDDETECTOR_DYNAMICDETECTOR_H

#include <ros/ros.h>
#include <Eigen/Eigen>
#include <Eigen/StdVector>
#include <cmath>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <visualization_msgs/MarkerArray.h>
#include <vision_msgs/Detection2DArray.h>
#include <image_transport/image_transport.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <onboard_detector/lidarDetector.h>
#include <onboard_detector/utils.h>
#include <onboard_detector/GetDynamicObstacles.h>
#include <onboard_detector/TargetBoxArray.h>

namespace onboardDetector{
    class dynamicDetector{
    private:
        std::string ns_;
        std::string hint_;

        // ROS
        ros::NodeHandle nh_;
        std::shared_ptr<message_filters::Subscriber<sensor_msgs::PointCloud2>> lidarCloudSub_;
        std::shared_ptr<message_filters::Subscriber<geometry_msgs::PoseStamped>> poseSub_;
        typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::PointCloud2, geometry_msgs::PoseStamped> lidarPoseSync;
        std::shared_ptr<message_filters::Synchronizer<lidarPoseSync>> lidarPoseSync_;
        std::shared_ptr<message_filters::Subscriber<nav_msgs::Odometry>> odomSub_;
        typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::PointCloud2, nav_msgs::Odometry> lidarOdomSync;
        std::shared_ptr<message_filters::Synchronizer<lidarOdomSync>> lidarOdomSync_;
        ros::Subscriber colorImgSub_;
        ros::Subscriber yoloDetectionSub_;
        ros::Timer detectionTimer_;
        ros::Timer lidarDetectionTimer_;
        ros::Timer visTimer_;
        image_transport::Publisher detectedColorImgPub_;
        ros::Publisher lidarBBoxesPub_;
        ros::Publisher filteredBBoxesBeforeYoloPub_;
        ros::Publisher filteredBBoxesPub_;
        ros::Publisher targetIdLabelsPub_;  // Publisher for target ID labels
        ros::Publisher confirmedTargetsPub_;  // Publisher for all confirmed targets boxes (for planner)
        ros::Publisher lidarClustersPub_;
        ros::Publisher downSamplePointsPub_;
        ros::ServiceServer getDynamicObstacleServer_;
    
        // DETECTOR
        std::shared_ptr<onboardDetector::lidarDetector> lidarDetector_;

        // SENSOR INFO
        // CAMERA COLOR
        double fxC_, fyC_, cxC_, cyC_;
        Eigen::Matrix4d body2CamColor_;

        // LIDAR
        Eigen::Matrix4d body2Lidar_;

        // PARAMETETER
        // Topics
        int localizationMode_;
        std::string colorImgTopicName_;
        std::string lidarTopicName_;
        std::string poseTopicName_;
        std::string odomTopicName_;

        // System
        double dt_;

        // DBSCAN Common
        double groundHeight_;
        double roofHeight_;
        
        // DBSCAN visual param
        double voxelOccThresh_;
        int dbMinPointsCluster_;
        double dbEpsilon_;
        
        // DBSCAN LiDAR param
        int lidarDBMinPoints_;
        double lidarDBEpsilon_;
        int gaussianDownSampleRate_;
        int downSampleThresh_;

        // LiDAR Visual Filtering
        double boxIOUThresh_;

        // Tracking and data association
        double maxMatchRange_;
        double maxMatchSizeRange_;
        Eigen::VectorXd featureWeights_;
        int histSize_;
        int fixSizeHistThresh_;
        double fixSizeDimThresh_;
        double eP_; // kalman filter initial uncertainty matrix
        double eQPos_; // motion model uncertainty matrix for position
        double eQVel_; // motion model uncertainty matrix for velocity
        double eQAcc_; // motion model uncertainty matrix for acceleration
        double eRPos_; // observation uncertainty matrix for position
        double eRVel_; // observation uncertainty matrix for velocity
        double eRAcc_; // observation uncertainty matrix for acceleration
        int kfAvgFrames_;

        // Classification
        int skipFrame_;
        double dynaVelThresh_;
        double dynaVoteThresh_;
        int forceDynaFrames_;
        int forceDynaCheckRange_;
        int dynamicConsistThresh_;

        // Constrain size
        bool constrainSize_;
        std::vector<Eigen::Vector3d> targetObjectSize_; 
        Eigen::Vector3d maxObjectSize_; 

        // SENSOR DATA
        Eigen::Vector3d position_; // robot position
        Eigen::Matrix3d orientation_; // robot orientation
        Eigen::Vector3d positionColor_; // color camera position
        Eigen::Matrix3d orientationColor_; // color camera orientation
        Eigen::Vector3d positionLidar_; // color camera position
        Eigen::Matrix3d orientationLidar_; // color camera orientation
        bool hasSensorPose_;
        Eigen::Vector3d localSensorRange_ {5.0, 5.0, 5.0};
        Eigen::Vector3d localLidarRange_ {10.0, 10.0, 5.0};

        //LIDAR DATA
        sensor_msgs::PointCloud2ConstPtr latestCloud_;
        pcl::PointCloud<pcl::PointXYZ>::Ptr lidarCloud_ = NULL; 
        std::vector<onboardDetector::Cluster> lidarClusters_;

        // DETECTOR DATA
        std::vector<onboardDetector::box3D> filteredBBoxesBeforeYolo_; // filtered bboxes before yolo
        std::vector<onboardDetector::box3D> filteredBBoxes_; // filtered bboxes (lidar + yolo fusion results)
        std::vector<std::vector<Eigen::Vector3d>> filteredPcClusters_; // pointcloud clusters after filtering
        std::vector<Eigen::Vector3d> filteredPcClusterCenters_; // filtered pointcloud cluster centers
        std::vector<Eigen::Vector3d> filteredPcClusterStds_; // filtered pointcloud cluster standard deviation in each axis
        std::vector<onboardDetector::box3D> lidarBBoxes_; // bboxes detected by lidar

        // Multi-frame fusion for robust detection
        struct DetectedTarget {
            onboardDetector::box3D box;
            int detectionCount;  // Number of times this target has been detected
            int missCount;       // Number of consecutive frames without detection
            double confidence;   // Confidence score (0-1)
            ros::Time lastSeen;  // Last time this target was seen
        };
        std::vector<DetectedTarget> detectedTargetsHistory_; // History of detected targets
        int minDetectionFrames_; // Minimum number of detections to confirm a target
        int maxMissFrames_;      // Maximum frames to keep a target after losing it
        double targetMatchIOU_;   // IOU threshold for matching targets across frames
        double confidenceDecay_; // Confidence decay rate per frame
        double targetMergeDistance_; // Distance threshold for merging nearby targets (meters)
        std::vector<onboardDetector::box3D> confirmedBBoxes_; // Confirmed stable targets

        // YOLO RESULTS
        vision_msgs::Detection2DArray yoloDetectionResults_; // yolo detected 2D results
        cv::Mat detectedColorImage_;

    public:
        dynamicDetector();
        dynamicDetector(const ros::NodeHandle& nh);
        void initDetector(const ros::NodeHandle& nh);

        void initParam();
        void registerPub();
        void registerCallback();

        // service
		bool getDynamicObstacles(onboard_detector::GetDynamicObstacles::Request& req, 
								 onboard_detector::GetDynamicObstacles::Response& res);

        // callback
        void lidarPoseCB(const sensor_msgs::PointCloud2ConstPtr& cloudMsg, const geometry_msgs::PoseStampedConstPtr& pose);
        void lidarOdomCB(const sensor_msgs::PointCloud2ConstPtr& cloudMsg, const nav_msgs::OdometryConstPtr& odom);
        void colorImgCB(const sensor_msgs::ImageConstPtr& img);
        void yoloDetectionCB(const vision_msgs::Detection2DArrayConstPtr& detections);
        void detectionCB(const ros::TimerEvent&);
        void lidarDetectionCB(const ros::TimerEvent&);
        void visCB(const ros::TimerEvent&);

        // detect function
        void lidarDetect();
        void filterLVBBoxes(); // filter lidar and yolo bounding boxes
        void multiFrameFusion(); // Multi-frame fusion for robust detection
        
        // detection helper functions
        double calBoxIOU(const onboardDetector::box3D& box1, const onboardDetector::box3D& box2, bool ignoreZmin=false);
        double calBoxDistance(const onboardDetector::box3D& box1, const onboardDetector::box3D& box2);  // Calculate distance between box centers
        std::vector<onboardDetector::box3D> mergeNearbyTargets(const std::vector<onboardDetector::box3D>& boxes, double mergeDistanceThreshold);  // Merge nearby targets

        // visualization
        void publishColorImages();
        void publish3dBox(const std::vector<onboardDetector::box3D>& bboxes, const ros::Publisher& publisher, double r, double g, double b);
        void publishTargetIdLabels(const std::vector<onboardDetector::box3D>& bboxes);  // Publish target ID labels
        void publishConfirmedTargets();  // Publish confirmed targets for planner
        void publishLidarClusters();

        // helper function
        void transformBBox(const Eigen::Vector3d& center, const Eigen::Vector3d& size, const Eigen::Vector3d& position, const Eigen::Matrix3d& orientation,
                                  Eigen::Vector3d& newCenter, Eigen::Vector3d& newSize);
        int getBestOverlapBBox(const onboardDetector::box3D& currBBox, const std::vector<onboardDetector::box3D>& targetBBoxes, double& bestIOU);

        // user functions
        void getDynamicObstacles(std::vector<onboardDetector::box3D>& incomeDynamicBBoxes, const Eigen::Vector3d &robotSize = Eigen::Vector3d(0.0,0.0,0.0));

        // inline helper functions
        void getCameraPose(const geometry_msgs::PoseStampedConstPtr& pose, Eigen::Matrix4d& camPoseColorMatrix);
        void getCameraPose(const nav_msgs::OdometryConstPtr& odom, Eigen::Matrix4d& camPoseColorMatrix);
        void getLidarPose(const geometry_msgs::PoseStampedConstPtr& pose, Eigen::Matrix4d& lidarPoseMatrix);
        void getLidarPose(const nav_msgs::OdometryConstPtr& odom, Eigen::Matrix4d& lidarPoseMatrix);       
    };


    inline void dynamicDetector::getCameraPose(const geometry_msgs::PoseStampedConstPtr& pose, Eigen::Matrix4d& camPoseColorMatrix){
        Eigen::Quaterniond quat;
        quat = Eigen::Quaterniond(pose->pose.orientation.w, pose->pose.orientation.x, pose->pose.orientation.y, pose->pose.orientation.z);
        Eigen::Matrix3d rot = quat.toRotationMatrix();

        // convert body pose to camera pose
        Eigen::Matrix4d map2body; map2body.setZero();
        map2body.block<3, 3>(0, 0) = rot;
        map2body(0, 3) = pose->pose.position.x; 
        map2body(1, 3) = pose->pose.position.y;
        map2body(2, 3) = pose->pose.position.z;
        map2body(3, 3) = 1.0;

        camPoseColorMatrix = map2body * this->body2CamColor_;
    }

    inline void dynamicDetector::getCameraPose(const nav_msgs::OdometryConstPtr& odom, Eigen::Matrix4d& camPoseColorMatrix){
        Eigen::Quaterniond quat;
        quat = Eigen::Quaterniond(odom->pose.pose.orientation.w, odom->pose.pose.orientation.x, odom->pose.pose.orientation.y, odom->pose.pose.orientation.z);
        Eigen::Matrix3d rot = quat.toRotationMatrix();

        // convert body pose to camera pose
        Eigen::Matrix4d map2body; map2body.setZero();
        map2body.block<3, 3>(0, 0) = rot;
        map2body(0, 3) = odom->pose.pose.position.x; 
        map2body(1, 3) = odom->pose.pose.position.y;
        map2body(2, 3) = odom->pose.pose.position.z;
        map2body(3, 3) = 1.0;

        camPoseColorMatrix = map2body * this->body2CamColor_;
    }

    inline void dynamicDetector::getLidarPose(const geometry_msgs::PoseStampedConstPtr& pose, Eigen::Matrix4d& lidarPoseMatrix){
        Eigen::Quaterniond quat;
        quat = Eigen::Quaterniond(pose->pose.orientation.w, pose->pose.orientation.x, pose->pose.orientation.y, pose->pose.orientation.z);
        Eigen::Matrix3d rot = quat.toRotationMatrix();

        // convert body pose to camera pose
        Eigen::Matrix4d map2body; map2body.setZero();
        map2body.block<3, 3>(0, 0) = rot;
        map2body(0, 3) = pose->pose.position.x; 
        map2body(1, 3) = pose->pose.position.y;
        map2body(2, 3) = pose->pose.position.z;
        map2body(3, 3) = 1.0;

        lidarPoseMatrix = map2body * this->body2Lidar_;
    }

    inline void dynamicDetector::getLidarPose(const nav_msgs::OdometryConstPtr& odom, Eigen::Matrix4d& lidarPoseMatrix){
        Eigen::Quaterniond quat;
        quat = Eigen::Quaterniond(odom->pose.pose.orientation.w, odom->pose.pose.orientation.x, odom->pose.pose.orientation.y, odom->pose.pose.orientation.z);
        Eigen::Matrix3d rot = quat.toRotationMatrix();

        // convert body pose to camera pose
        Eigen::Matrix4d map2body; map2body.setZero();
        map2body.block<3, 3>(0, 0) = rot;
        map2body(0, 3) = odom->pose.pose.position.x; 
        map2body(1, 3) = odom->pose.pose.position.y;
        map2body(2, 3) = odom->pose.pose.position.z;
        map2body(3, 3) = 1.0;

        lidarPoseMatrix = map2body * this->body2Lidar_;
    }
}

#endif
