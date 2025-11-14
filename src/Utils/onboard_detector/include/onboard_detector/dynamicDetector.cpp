/*
    FILE: dynamicDetector.cpp
    ---------------------------------
    function implementation of dynamic osbtacle detector
*/
#include <onboard_detector/dynamicDetector.h>

namespace onboardDetector{
    dynamicDetector::dynamicDetector(){
        this->ns_ = "onboard_detector";
        this->hint_ = "[onboardDetector]";
    }

    dynamicDetector::dynamicDetector(const ros::NodeHandle& nh){
        this->ns_ = "onboard_detector";
        this->hint_ = "[onboardDetector]";
        this->nh_ = nh;
        this->initParam();
        this->registerPub();
        this->registerCallback();
    }

    void dynamicDetector::initDetector(const ros::NodeHandle& nh){
        this->nh_ = nh;
        this->initParam();
        this->registerPub();
        this->registerCallback();
    }

    void dynamicDetector::initParam(){
        // Helper lambda for parameter loading with default value
        auto getParam = [this](const std::string& paramName, auto& value, const auto& defaultValue, const std::string& desc = "") {
            if (not this->nh_.getParam(this->ns_ + "/" + paramName, value)) {
                value = defaultValue;
                std::cout << this->hint_ << ": No " << desc << " parameter. Use default: " << defaultValue << std::endl;
            } else {
                std::cout << this->hint_ << ": " << desc << " is set to: " << value << std::endl;
            }
        };

        // Topics
        getParam("localization_mode", this->localizationMode_, 0, "localization mode");
        getParam("color_image_topic", this->colorImgTopicName_, std::string("/camera/color/image_raw"), "color image topic");
        getParam("lidar_pointcloud_topic", this->lidarTopicName_, std::string("/cloud_registered"), "lidar pointcloud topic");
        
        if (this->localizationMode_ == 0) {
            getParam("pose_topic", this->poseTopicName_, std::string("/CERLAB/quadcopter/pose"), "pose topic");
        } else if (this->localizationMode_ == 1) {
            getParam("odom_topic", this->odomTopicName_, std::string("/CERLAB/quadcopter/odom"), "odom topic");
        }

        // Camera intrinsics (required)
        std::vector<double> colorIntrinsics(4);
        if (not this->nh_.getParam(this->ns_ + "/color_intrinsics", colorIntrinsics)) {
            ROS_ERROR("[dynamicDetector]: Please check camera intrinsics!");
            exit(0);
        }
        this->fxC_ = colorIntrinsics[0];
        this->fyC_ = colorIntrinsics[1];
        this->cxC_ = colorIntrinsics[2];
        this->cyC_ = colorIntrinsics[3];
        std::cout << this->hint_ << ": fxC, fyC, cxC, cyC: [" << this->fxC_ << ", " << this->fyC_ << ", " << this->cxC_ << ", " << this->cyC_ << "]" << std::endl;

        // Transform matrices (required)
        auto loadMatrix = [this](const std::string& paramName, Eigen::Matrix4d& matrix) {
            std::vector<double> vec(16);
            std::string fullParamName = this->ns_ + "/" + paramName;
            if (not this->nh_.getParam(fullParamName, vec)) {
                ROS_ERROR("[dynamicDetector]: Please check %s matrix!", fullParamName.c_str());
                return;
            }
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    matrix(i, j) = vec[i * 4 + j];
                }
            }
            // ROS_INFO("[dynamicDetector]: Loaded %s matrix:", paramName.c_str());
            // ROS_INFO("[dynamicDetector]:   [%.4f, %.4f, %.4f, %.4f]", matrix(0,0), matrix(0,1), matrix(0,2), matrix(0,3));
            // ROS_INFO("[dynamicDetector]:   [%.4f, %.4f, %.4f, %.4f]", matrix(1,0), matrix(1,1), matrix(1,2), matrix(1,3));
            // ROS_INFO("[dynamicDetector]:   [%.4f, %.4f, %.4f, %.4f]", matrix(2,0), matrix(2,1), matrix(2,2), matrix(2,3));
            // ROS_INFO("[dynamicDetector]:   [%.4f, %.4f, %.4f, %.4f]", matrix(3,0), matrix(3,1), matrix(3,2), matrix(3,3));
        };
        loadMatrix("body_to_camera_color", this->body2CamColor_);
        loadMatrix("body_to_lidar", this->body2Lidar_);

        // System parameters
        getParam("time_step", this->dt_, 0.033, "time step");
        getParam("ground_height", this->groundHeight_, 0.1, "ground height");
        getParam("roof_height", this->roofHeight_, 2.0, "roof height");

        // DBSCAN parameters
        getParam("voxel_occupied_thresh", this->voxelOccThresh_, 10, "voxel occupied threshold");
        getParam("dbscan_min_points_cluster", this->dbMinPointsCluster_, 18, "DBSCAN min points");
        getParam("dbscan_search_range_epsilon", this->dbEpsilon_, 0.3, "DBSCAN epsilon");
        getParam("lidar_DBSCAN_min_points", this->lidarDBMinPoints_, 10, "lidar DBSCAN min points");
        getParam("lidar_DBSCAN_epsilon", this->lidarDBEpsilon_, 0.2, "lidar DBSCAN epsilon");
        
        // Downsampling parameters
        getParam("downsample_threshold", this->downSampleThresh_, 4000, "downsample threshold");
        getParam("gaussian_downsample_rate", this->gaussianDownSampleRate_, 2, "gaussian downsample rate");

        // Filtering parameters
        getParam("filtering_BBox_IOU_threshold", this->boxIOUThresh_, 0.5, "IOU threshold");
        getParam("max_match_range", this->maxMatchRange_, 0.5, "max match range");
        getParam("max_size_diff_range", this->maxMatchSizeRange_, 0.5, "max size difference range");   

        // Feature weights
        std::vector<double> tempWeights;
        if (not nh_.getParam(ns_ + "/feature_weight", tempWeights)) {
            this->featureWeights_ = Eigen::VectorXd(10);
            this->featureWeights_ << 3.0, 3.0, 0.1, 0.5, 0.5, 0.05, 0, 0, 0, 0;
            std::cout << this->hint_ << ": No feature weights parameter found. Using default: [3.0, 3.0, 0.1, 0.5, 0.5, 0.05, 0, 0, 0, 0]." << std::endl;
        } else {
            this->featureWeights_ = Eigen::Map<Eigen::VectorXd>(tempWeights.data(), tempWeights.size());
            std::cout << this->hint_ << ": Feature weights: [";
            for (size_t i = 0; i < tempWeights.size(); ++i) {
                std::cout << tempWeights[i] << (i < tempWeights.size()-1 ? ", " : "");
            }
            std::cout << "]." << std::endl;
        }

        // Tracking parameters
        getParam("history_size", this->histSize_, 5, "tracking history size");
        getParam("fix_size_history_threshold", this->fixSizeHistThresh_, 10, "fix size history threshold");
        getParam("fix_size_dimension_threshold", this->fixSizeDimThresh_, 0.4, "fix size dimension threshold"); 

        // Kalman filter parameters
        std::vector<double> kalmanFilterParams;
        if (not this->nh_.getParam(this->ns_ + "/kalman_filter_param", kalmanFilterParams)) {
            this->eP_ = this->eQPos_ = this->eQVel_ = this->eQAcc_ = this->eRPos_ = this->eRVel_ = this->eRAcc_ = 0.5;
            std::cout << this->hint_ << ": No kalman filter parameter found. Use default: 0.5." << std::endl;
        } else {
            this->eP_ = kalmanFilterParams[0];
            this->eQPos_ = kalmanFilterParams[1];
            this->eQVel_ = kalmanFilterParams[2];
            this->eQAcc_ = kalmanFilterParams[3];
            this->eRPos_ = kalmanFilterParams[4];
            this->eRVel_ = kalmanFilterParams[5];
            this->eRAcc_ = kalmanFilterParams[6];
            std::cout << this->hint_ << ": Kalman filter params: [";
            for (size_t i = 0; i < kalmanFilterParams.size(); ++i) {
                std::cout << kalmanFilterParams[i] << (i < kalmanFilterParams.size()-1 ? ", " : "");
            }
            std::cout << "]." << std::endl;
        }
        getParam("kalman_filter_averaging_frames", this->kfAvgFrames_, 10, "KF averaging frames");

        // Classification parameters
        getParam("frame_skip", this->skipFrame_, 5, "frame skip");
        getParam("dynamic_velocity_threshold", this->dynaVelThresh_, 0.35, "dynamic velocity threshold");
        getParam("dynamic_voting_threshold", this->dynaVoteThresh_, 0.8, "dynamic voting threshold");
        getParam("frames_force_dynamic", this->forceDynaFrames_, 20, "frames force dynamic");
        getParam("frames_force_dynamic_check_range", this->forceDynaCheckRange_, 30, "force dynamic check range");
        getParam("dynamic_consistency_threshold", this->dynamicConsistThresh_, 3, "dynamic consistency threshold");

        if (this->histSize_ < this->forceDynaCheckRange_ + 1) {
            ROS_ERROR("history length is too short to perform force-dynamic");
        }

        // Multi-frame fusion parameters
        getParam("min_detection_frames", this->minDetectionFrames_, 3, "min detection frames to confirm target");
        getParam("max_miss_frames", this->maxMissFrames_, 5, "max miss frames before removing target");
        getParam("target_match_IOU", this->targetMatchIOU_, 0.3, "IOU threshold for matching targets");
        getParam("confidence_decay", this->confidenceDecay_, 0.1, "confidence decay per frame");
        getParam("target_merge_distance", this->targetMergeDistance_, 1.0, "distance threshold for merging nearby targets");

        // Object size constraints
        getParam("target_constrain_size", this->constrainSize_, false, "target constrain size");
        
        std::vector<double> targetObjectSizeTemp;
        if (this->nh_.getParam(this->ns_ + "/target_object_size", targetObjectSizeTemp)) {
            for (size_t i = 0; i < targetObjectSizeTemp.size(); i += 3) {
                Eigen::Vector3d targetSize(targetObjectSizeTemp[i], targetObjectSizeTemp[i+1], targetObjectSizeTemp[i+2]);
                this->targetObjectSize_.push_back(targetSize);
                std::cout << this->hint_ << ": Target object size: [" << targetSize.transpose() << "]" << std::endl;
            }
        }

        std::vector<double> maxObjectSizeTemp;
        if (this->nh_.getParam(this->ns_ + "/max_object_size", maxObjectSizeTemp)) {
            this->maxObjectSize_ = Eigen::Vector3d(maxObjectSizeTemp[0], maxObjectSizeTemp[1], maxObjectSizeTemp[2]);
            std::cout << this->hint_ << ": Max object size: [" << this->maxObjectSize_.transpose() << "]" << std::endl;
        } else {
            this->maxObjectSize_ = Eigen::Vector3d(2.0, 2.0, 2.0);
            std::cout << this->hint_ << ": No max object size parameter found. Use default: [2.0, 2.0, 2.0]." << std::endl;
        }
    }

    void dynamicDetector::registerPub(){
        image_transport::ImageTransport it(this->nh_);

        // color 2D bounding boxes pub
        this->detectedColorImgPub_ = it.advertise(this->ns_ + "/detected_color_image", 10);

        // lidar bbox pub
        this->lidarBBoxesPub_ = this->nh_.advertise<visualization_msgs::MarkerArray>(this->ns_ + "/lidar_bboxes", 10);

        // filtered bounding box before YOLO pub
        this->filteredBBoxesBeforeYoloPub_ = this->nh_.advertise<visualization_msgs::MarkerArray>(this->ns_ + "/filtered_before_yolo_bboxes", 10);

        // filtered bounding box pub
        this->filteredBBoxesPub_ = this->nh_.advertise<visualization_msgs::MarkerArray>(this->ns_ + "/filtered_bboxes", 10);

        // target ID labels pub
        this->targetIdLabelsPub_ = this->nh_.advertise<visualization_msgs::MarkerArray>(this->ns_ + "/target_id_labels", 10);

        // confirmed targets boxes pub (all confirmed targets for planner)
        this->confirmedTargetsPub_ = this->nh_.advertise<onboard_detector::TargetBoxArray>(this->ns_ + "/confirmed_targets", 10);

        // lidar cluster pub 
        this->lidarClustersPub_ = this->nh_.advertise<sensor_msgs::PointCloud2>(this->ns_ + "/lidar_clusters", 10);

        // downsample points visualization pub
        this->downSamplePointsPub_ = this->nh_.advertise<sensor_msgs::PointCloud2>(this->ns_ + "/downsampled_point_cloud", 10);
    }   

    void dynamicDetector::registerCallback(){
        this->lidarCloudSub_.reset(new message_filters::Subscriber<sensor_msgs::PointCloud2>(this->nh_, this->lidarTopicName_, 50));
        // this->lidarCloudSub_ = this->nh_.subscribe(this->lidarTopicName_, 10, &dynamicDetector::lidarCloudCB, this);
        if (this->localizationMode_ == 0){
            this->poseSub_.reset(new message_filters::Subscriber<geometry_msgs::PoseStamped>(this->nh_, this->poseTopicName_, 25));
            this->lidarPoseSync_.reset(new message_filters::Synchronizer<lidarPoseSync>(lidarPoseSync(100), *this->lidarCloudSub_, *this->poseSub_));
            this->lidarPoseSync_->registerCallback(boost::bind(&dynamicDetector::lidarPoseCB, this, _1, _2));
        }
        else if (this->localizationMode_ == 1){
            this->odomSub_.reset(new message_filters::Subscriber<nav_msgs::Odometry>(this->nh_, this->odomTopicName_, 25));
            this->lidarOdomSync_.reset(new message_filters::Synchronizer<lidarOdomSync>(lidarOdomSync(100), *this->lidarCloudSub_, *this->odomSub_));
            this->lidarOdomSync_->registerCallback(boost::bind(&dynamicDetector::lidarOdomCB, this, _1, _2));
        }
        else{
            ROS_ERROR("[dynamicDetector]: Invalid localization mode!");
            exit(0);
        }

        // color image subscriber
        this->colorImgSub_ = this->nh_.subscribe(this->colorImgTopicName_, 10, &dynamicDetector::colorImgCB, this);

        // yolo detection results subscriber
        this->yoloDetectionSub_ = this->nh_.subscribe("yolo_detector/detected_bounding_boxes", 10, &dynamicDetector::yoloDetectionCB, this);

        // detection timer
        this->detectionTimer_ = this->nh_.createTimer(ros::Duration(this->dt_), &dynamicDetector::detectionCB, this);

        // lidar detection timer
        this->lidarDetectionTimer_ = this->nh_.createTimer(ros::Duration(this->dt_), &dynamicDetector::lidarDetectionCB, this);
    
        // visualization timer
        this->visTimer_ = this->nh_.createTimer(ros::Duration(this->dt_), &dynamicDetector::visCB, this);
        
		// get dynamic obstacle service
		this->getDynamicObstacleServer_ = this->nh_.advertiseService("onboard_detector/get_dynamic_obstacles", &dynamicDetector::getDynamicObstacles, this);
    }

    bool dynamicDetector::getDynamicObstacles(onboard_detector::GetDynamicObstacles::Request& req, 
                                              onboard_detector::GetDynamicObstacles::Response& res) {
        // Get the current robot position
        Eigen::Vector3d currPos = Eigen::Vector3d (req.current_position.x, req.current_position.y, req.current_position.z);

        // Vector to store obstacles along with their distances
        std::vector<std::pair<double, onboardDetector::box3D>> obstaclesWithDistances;

        // Go through all obstacles and calculate distances (use filteredBBoxes_ which contains lidar+yolo results)
        for (const onboardDetector::box3D& bbox : this->filteredBBoxes_) {
            Eigen::Vector3d obsPos(bbox.x, bbox.y, bbox.z);
            Eigen::Vector3d diff = currPos - obsPos;
            diff(2) = 0.;
            double distance = diff.norm();
            if (distance <= req.range) {
                obstaclesWithDistances.push_back(std::make_pair(distance, bbox));
            }
        }

        // Sort obstacles by distance in ascending order
        std::sort(obstaclesWithDistances.begin(), obstaclesWithDistances.end(), 
                [](const std::pair<double, onboardDetector::box3D>& a, const std::pair<double, onboardDetector::box3D>& b) {
                    return a.first < b.first;
                });

        // Push sorted obstacles into the response
        for (const auto& item : obstaclesWithDistances) {
            const onboardDetector::box3D& bbox = item.second;

            geometry_msgs::Vector3 pos;
            geometry_msgs::Vector3 vel;
            geometry_msgs::Vector3 size;

            pos.x = bbox.x;
            pos.y = bbox.y;
            pos.z = bbox.z;

            vel.x = bbox.Vx;
            vel.y = bbox.Vy;
            vel.z = 0.;

            size.x = bbox.x_width;
            size.y = bbox.y_width;
            size.z = bbox.z_width;

            res.position.push_back(pos);
            res.velocity.push_back(vel);
            res.size.push_back(size);
        }

        return true;
    }

    void dynamicDetector::lidarPoseCB(const sensor_msgs::PointCloud2ConstPtr& cloudMsg, const geometry_msgs::PoseStampedConstPtr& pose){
        // for visualization
        this->latestCloud_ = cloudMsg;

        // local cloud
        pcl::PointCloud<pcl::PointXYZ>::Ptr tempCloud (new pcl::PointCloud<pcl::PointXYZ>());
        pcl::fromROSMsg(*cloudMsg, *tempCloud);

        // filter and downsample pointcloud
        // Create a filtered cloud pointer to store intermediate results
        pcl::PointCloud<pcl::PointXYZ>::Ptr filteredCloud (new pcl::PointCloud<pcl::PointXYZ>());

        // Apply a pass-through filter to limit points to the local sensor range in X, Y, and Z axes
        pcl::PassThrough<pcl::PointXYZ> pass;

        // Filter for X axis
        pass.setInputCloud(tempCloud);
        pass.setFilterFieldName("x");
        pass.setFilterLimits(-this->localLidarRange_.x(), this->localLidarRange_.x());
        pass.filter(*filteredCloud);

        // Filter for Y axis
        pass.setInputCloud(filteredCloud);
        pass.setFilterFieldName("y");
        pass.setFilterLimits(-this->localLidarRange_.y(), this->localLidarRange_.y());
        pass.filter(*filteredCloud);

        int sigma = this->gaussianDownSampleRate_;

        pcl::PointCloud<pcl::PointXYZ>::Ptr preTransformCloud(new pcl::PointCloud<pcl::PointXYZ>());
        preTransformCloud->reserve(filteredCloud->size());

        for (pcl::PointXYZ &pt : filteredCloud->points) {
            double dist = pow(pow(pt.x, 2) + pow(pt.y, 2), 0.5);
            double p = std::exp(-(dist * dist) / (2 * sigma * sigma));

            double r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            if (r < p) {
                preTransformCloud->push_back(pt);
            }
        }

        // transform
        Eigen::Affine3d transform = Eigen::Affine3d::Identity();
        transform.linear() = this->orientationLidar_;
        transform.translation() = this->positionLidar_;

        // map cloud
        // Create an empty point cloud to store the transformed data
        pcl::PointCloud<pcl::PointXYZ>::Ptr transformedCloud (new pcl::PointCloud<pcl::PointXYZ>());

        // Apply the transformation
        pcl::transformPointCloud(*preTransformCloud, *transformedCloud, transform);

        // filter roof and ground 
        pcl::PointCloud<pcl::PointXYZ>::Ptr groundRoofFilterCloud (new pcl::PointCloud<pcl::PointXYZ>());
        pass.setInputCloud(transformedCloud);
        pass.setFilterFieldName("z");
        pass.setFilterLimits(this->groundHeight_, this->roofHeight_);
        pass.filter(*groundRoofFilterCloud);

        pcl::PointCloud<pcl::PointXYZ>::Ptr downsampledCloud = groundRoofFilterCloud;
        // Create the VoxelGrid filter object
        pcl::VoxelGrid<pcl::PointXYZ> sor;
        // sor.setInputCloud(filteredCloud);
        sor.setInputCloud(groundRoofFilterCloud);

        // Set the leaf size (adjust to control the downsampling)
        sor.setLeafSize(0.1f, 0.1f, 0.1f); // Try different values based on your point cloud density

        // If the downsampled cloud has more than certain points, further increase the leaf size
        while (int(downsampledCloud->size()) > this->downSampleThresh_) {
            double leafSize = sor.getLeafSize().x() * 1.1f; // Increase the leaf size to reduce point count
            sor.setLeafSize(leafSize, leafSize, leafSize);
            sor.filter(*downsampledCloud);
        }

        this->lidarCloud_ = downsampledCloud;
        sensor_msgs::PointCloud2 outputCloud;
        pcl::toROSMsg(*this->lidarCloud_, outputCloud); // Convert to ROS message
        outputCloud.header.frame_id = "world";    // Set appropriate frame ID
        this->downSamplePointsPub_.publish(outputCloud);

        // store current position and orientation
        Eigen::Matrix4d lidarPoseMatrix;
        this->getLidarPose(pose, lidarPoseMatrix);

        // store current position and orientation (camera)
        Eigen::Matrix4d camPoseColorMatrix;
        this->getCameraPose(pose, camPoseColorMatrix);

        this->position_(0) = pose->pose.position.x;
        this->position_(1) = pose->pose.position.y;
        this->position_(2) = pose->pose.position.z;
        Eigen::Quaterniond quat;
        quat = Eigen::Quaterniond(pose->pose.orientation.w, pose->pose.orientation.x, pose->pose.orientation.y, pose->pose.orientation.z);
        Eigen::Matrix3d rot = quat.toRotationMatrix();
        this->orientation_ = rot;

        this->positionColor_(0) = camPoseColorMatrix(0, 3);
        this->positionColor_(1) = camPoseColorMatrix(1, 3);
        this->positionColor_(2) = camPoseColorMatrix(2, 3);
        this->orientationColor_ = camPoseColorMatrix.block<3, 3>(0, 0);

        this->positionLidar_(0) = lidarPoseMatrix(0, 3);
        this->positionLidar_(1) = lidarPoseMatrix(1, 3);
        this->positionLidar_(2) = lidarPoseMatrix(2, 3);
        this->orientationLidar_ = lidarPoseMatrix.block<3, 3>(0, 0);
    }

    void dynamicDetector::lidarOdomCB(const sensor_msgs::PointCloud2ConstPtr& cloudMsg, const nav_msgs::OdometryConstPtr& odom){
        // for visualization
        this->latestCloud_ = cloudMsg;

        // local cloud
        pcl::PointCloud<pcl::PointXYZ>::Ptr tempCloud (new pcl::PointCloud<pcl::PointXYZ>());
        pcl::fromROSMsg(*cloudMsg, *tempCloud);

        // filter and downsample pointcloud
        // Create a filtered cloud pointer to store intermediate results
        pcl::PointCloud<pcl::PointXYZ>::Ptr filteredCloud (new pcl::PointCloud<pcl::PointXYZ>());

        // Apply a pass-through filter to limit points to the local sensor range in X, Y, and Z axes
        pcl::PassThrough<pcl::PointXYZ> pass;

        // Filter for X axis
        pass.setInputCloud(tempCloud);
        pass.setFilterFieldName("x");
        pass.setFilterLimits(-this->localLidarRange_.x(), this->localLidarRange_.x());
        pass.filter(*filteredCloud);

        // Filter for Y axis
        pass.setInputCloud(filteredCloud);
        pass.setFilterFieldName("y");
        pass.setFilterLimits(-this->localLidarRange_.y(), this->localLidarRange_.y());
        pass.filter(*filteredCloud);

        int sigma = this->gaussianDownSampleRate_;

        pcl::PointCloud<pcl::PointXYZ>::Ptr preTransformCloud(new pcl::PointCloud<pcl::PointXYZ>());
        preTransformCloud->reserve(filteredCloud->size());

        for (pcl::PointXYZ &pt : filteredCloud->points) {
            double dist = pow(pow(pt.x, 2) + pow(pt.y, 2), 0.5);
            double p = std::exp(-(dist * dist) / (2 * sigma * sigma));

            double r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            if (r < p) {
                preTransformCloud->push_back(pt);
            }
        }

        // transform
        Eigen::Affine3d transform = Eigen::Affine3d::Identity();
        transform.linear() = this->orientationLidar_;
        transform.translation() = this->positionLidar_;

        // map cloud
        // Create an empty point cloud to store the transformed data
        pcl::PointCloud<pcl::PointXYZ>::Ptr transformedCloud (new pcl::PointCloud<pcl::PointXYZ>());

        // Apply the transformation
        pcl::transformPointCloud(*preTransformCloud, *transformedCloud, transform);

        // filter roof and ground 
        pcl::PointCloud<pcl::PointXYZ>::Ptr groundRoofFilterCloud (new pcl::PointCloud<pcl::PointXYZ>());
        pass.setInputCloud(transformedCloud);
        pass.setFilterFieldName("z");
        pass.setFilterLimits(this->groundHeight_, this->roofHeight_);
        pass.filter(*groundRoofFilterCloud);

        pcl::PointCloud<pcl::PointXYZ>::Ptr downsampledCloud = groundRoofFilterCloud;
        // Create the VoxelGrid filter object
        pcl::VoxelGrid<pcl::PointXYZ> sor;
        // sor.setInputCloud(filteredCloud);
        sor.setInputCloud(groundRoofFilterCloud);

        // Set the leaf size (adjust to control the downsampling)
        sor.setLeafSize(0.1f, 0.1f, 0.1f); // Try different values based on your point cloud density

        // If the downsampled cloud has more than certain points, further increase the leaf size
        while (int(downsampledCloud->size()) > this->downSampleThresh_) {
            double leafSize = sor.getLeafSize().x() * 1.1f; // Increase the leaf size to reduce point count
            sor.setLeafSize(leafSize, leafSize, leafSize);
            sor.filter(*downsampledCloud);
        }

        this->lidarCloud_ = downsampledCloud;
        sensor_msgs::PointCloud2 outputCloud;
        pcl::toROSMsg(*this->lidarCloud_, outputCloud); // Convert to ROS message
        outputCloud.header.frame_id = "world";    // Set appropriate frame ID
        this->downSamplePointsPub_.publish(outputCloud);
        
        // store current position and orientation
        Eigen::Matrix4d lidarPoseMatrix;
        this->getLidarPose(odom, lidarPoseMatrix);

        // store current position and orientation (camera)
        Eigen::Matrix4d camPoseColorMatrix;
        this->getCameraPose(odom, camPoseColorMatrix);

        this->position_(0) = odom->pose.pose.position.x;
        this->position_(1) = odom->pose.pose.position.y;
        this->position_(2) = odom->pose.pose.position.z;
        Eigen::Quaterniond quat;
        quat = Eigen::Quaterniond(odom->pose.pose.orientation.w, odom->pose.pose.orientation.x, odom->pose.pose.orientation.y, odom->pose.pose.orientation.z);
        Eigen::Matrix3d rot = quat.toRotationMatrix();
        this->orientation_ = rot;

        this->positionColor_(0) = camPoseColorMatrix(0, 3);
        this->positionColor_(1) = camPoseColorMatrix(1, 3);
        this->positionColor_(2) = camPoseColorMatrix(2, 3);
        this->orientationColor_ = camPoseColorMatrix.block<3, 3>(0, 0);

        this->positionLidar_(0) = lidarPoseMatrix(0, 3);
        this->positionLidar_(1) = lidarPoseMatrix(1, 3);
        this->positionLidar_(2) = lidarPoseMatrix(2, 3);
        this->orientationLidar_ = lidarPoseMatrix.block<3, 3>(0, 0);
    }

    void dynamicDetector::colorImgCB(const sensor_msgs::ImageConstPtr& img){
        cv_bridge::CvImagePtr imgPtr = cv_bridge::toCvCopy(img, img->encoding);
        imgPtr->image.copyTo(this->detectedColorImage_);
    }

    void dynamicDetector::yoloDetectionCB(const vision_msgs::Detection2DArrayConstPtr& detections){
        this->yoloDetectionResults_ = *detections;
    }

   
    void dynamicDetector::lidarDetectionCB(const ros::TimerEvent&){
        this->lidarDetect();
    }

    void dynamicDetector::detectionCB(const ros::TimerEvent&){
        // detection thread - only lidar and yolo fusion
        this->filterLVBBoxes();
        
        // Multi-frame fusion for robust detection
        this->multiFrameFusion();
    }


    void dynamicDetector::visCB(const ros::TimerEvent&){
        this->publishColorImages();
        this->publish3dBox(this->lidarBBoxes_, this->lidarBBoxesPub_, 0.5, 0.5, 0.5); // raw lidar cluster bounding boxes
        this->publish3dBox(this->filteredBBoxesBeforeYolo_, this->filteredBBoxesBeforeYoloPub_, 0, 1, 0.5);
        this->publish3dBox(this->filteredBBoxes_, this->filteredBBoxesPub_, 0, 1, 1);
        this->publishTargetIdLabels(this->filteredBBoxes_);  // Publish target ID labels
        this->publishConfirmedTargets();  // Publish confirmed targets for planner
        this->publishLidarClusters(); // colored clusters
    }



    void dynamicDetector::lidarDetect(){
        if (this->lidarDetector_ == NULL){
            this->lidarDetector_.reset(new lidarDetector());
            this->lidarDetector_->setParams(this->lidarDBEpsilon_, this->lidarDBMinPoints_);
        }

        if (this->lidarCloud_ != NULL){
            this->lidarDetector_->getPointcloud(this->lidarCloud_);
            this->lidarDetector_->lidarDBSCAN();

            std::vector<onboardDetector::Cluster> lidarClustersRaw = this->lidarDetector_->getClusters();
            std::vector<onboardDetector::Cluster> lidarClustersFiltered;
            std::vector<onboardDetector::box3D> lidarBBoxesRaw = this->lidarDetector_->getBBoxes();
            std::vector<onboardDetector::box3D> lidarBBoxesFiltered;
            for (int i=0; i<int(lidarBBoxesRaw.size()); ++i){
                onboardDetector::box3D lidarBBox = lidarBBoxesRaw[i];
                // filter out lidar bounding boxes that are too large
                if(lidarBBox.x_width > this->maxObjectSize_(0) || lidarBBox.y_width > this->maxObjectSize_(1) || lidarBBox.z_width > this->maxObjectSize_(2)){
                    continue;
                }
                lidarBBoxesFiltered.push_back(lidarBBox);
                lidarClustersFiltered.push_back(lidarClustersRaw[i]);            
            }
            this->lidarBBoxes_ = lidarBBoxesFiltered;
            this->lidarClusters_ = lidarClustersFiltered;
        }
    }

    void dynamicDetector::filterLVBBoxes(){
        std::vector<onboardDetector::box3D> filteredBBoxesTemp;
        std::vector<std::vector<Eigen::Vector3d>> filteredPcClustersTemp;
        std::vector<Eigen::Vector3d> filteredPcClusterCentersTemp;
        std::vector<Eigen::Vector3d> filteredPcClusterStdsTemp; 

        // STEP 1: Get lidar bboxes and its corresponding clusters and features
        if (this->lidarBBoxes_.size() != this->lidarClusters_.size()) {
            // ROS_WARN("[dynamicDetector]: lidarBBoxes_ and lidarClusters_ size mismatch: %zu vs %zu", 
            //          this->lidarBBoxes_.size(), this->lidarClusters_.size());
            return;
        }
        
        for (size_t i = 0; i < this->lidarBBoxes_.size(); ++i) {
            onboardDetector::box3D lidarBBox = this->lidarBBoxes_[i];
            
            // get corresponding point cloud cluster
            onboardDetector::Cluster cluster = this->lidarClusters_[i];
            
            // Check if cluster points is valid
            if (cluster.points == nullptr || cluster.points->points.empty()) {
                // ROS_WARN("[dynamicDetector]: Invalid cluster at index %zu, skipping", i);
                continue;
            }

            std::vector<Eigen::Vector3d> pcCluster;
            for (const pcl::PointXYZ& point : cluster.points->points) {
                pcCluster.emplace_back(point.x, point.y, point.z);
            }

            // extract the cluster center
            Eigen::Vector3d clusterCenter(cluster.centroid[0], cluster.centroid[1], cluster.centroid[2]);

            // compute std
            Eigen::Vector3d clusterStd = cluster.eigen_values.cwiseSqrt().cast<double>();

            filteredBBoxesTemp.push_back(lidarBBox);
            filteredPcClustersTemp.push_back(pcCluster);
            filteredPcClusterCentersTemp.push_back(clusterCenter);
            filteredPcClusterStdsTemp.push_back(clusterStd);
        }
        this->filteredBBoxesBeforeYolo_ = filteredBBoxesTemp;

        // STEP 2: Only keep 3D boxes that match YOLO detections
        // If no YOLO detection results, keep existing confirmed boxes (don't clear)
        if (this->yoloDetectionResults_.detections.size() == 0){
            // ROS_WARN("[dynamicDetector]: No YOLO detections, clearing all filtered boxes");
            // Don't clear filteredBBoxes_, keep confirmed targets
            // Only clear temporary filtered data that are not confirmed yet
            // filteredBBoxes_ will be updated by multiFrameFusion with confirmed targets
            return;
        }

        // ROS_DEBUG("[dynamicDetector]: Processing %zu lidar boxes and %zu YOLO detections", 
        //           filteredBBoxesTemp.size(), this->yoloDetectionResults_.detections.size());

        // If YOLO detection results are available, only keep boxes that match YOLO detections
        {
            std::vector<int> best3DBBoxForYOLO(this->yoloDetectionResults_.detections.size(), -1);

            // Project 2D bbox in color image plane from 3D
            vision_msgs::Detection2DArray filteredDetectionResults;
            int skippedBehindCamera = 0;
            for (int j=0; j<int(filteredBBoxesTemp.size()); ++j){
                onboardDetector::box3D bbox = filteredBBoxesTemp[j];

                // 1. transform the bounding boxes into the camera frame
                Eigen::Vector3d centerWorld (bbox.x, bbox.y, bbox.z);
                Eigen::Vector3d sizeWorld (bbox.x_width, bbox.y_width, bbox.z_width);
                Eigen::Vector3d centerCam, sizeCam;
                this->transformBBox(centerWorld, sizeWorld, -this->orientationColor_.inverse() * this->positionColor_, this->orientationColor_.inverse(), centerCam, sizeCam);

                // 2. find the top left and bottom right corner 3D position of the transformed bbox
                Eigen::Vector3d topleft (centerCam(0)-sizeCam(0)/2, centerCam(1)-sizeCam(1)/2, centerCam(2));
                Eigen::Vector3d bottomright (centerCam(0)+sizeCam(0)/2, centerCam(1)+sizeCam(1)/2, centerCam(2));

                // 3. project those two points into the camera image plane
                // Check if point is in front of camera
                if (topleft(2) <= 0 || bottomright(2) <= 0) {
                    skippedBehindCamera++;
                    continue; // Skip boxes behind camera
                }

                int tlX = int((this->fxC_ * topleft(0) + this->cxC_ * topleft(2)) / topleft(2));
                int tlY = int((this->fyC_ * topleft(1) + this->cyC_ * topleft(2)) / topleft(2));
                int brX = int((this->fxC_ * bottomright(0) + this->cxC_ * bottomright(2)) / bottomright(2));
                int brY = int((this->fyC_ * bottomright(1) + this->cyC_ * bottomright(2)) / bottomright(2));

                // Check if projected box is valid and within image bounds
                if (brX <= tlX || brY <= tlY) {
                    // ROS_DEBUG("[dynamicDetector]: Invalid projected box %d: tl=(%d,%d), br=(%d,%d)", 
                    //           j, tlX, tlY, brX, brY);
                    continue;
                }
                
                vision_msgs::Detection2D result;
                result.bbox.center.x = tlX;
                result.bbox.center.y = tlY;
                result.bbox.size_x = brX - tlX;
                result.bbox.size_y = brY - tlY;
                filteredDetectionResults.detections.push_back(result);
                
                // ROS_DEBUG("[dynamicDetector]: 3D box %d projected to image: tl=(%d,%d), br=(%d,%d), center=(%.2f,%.2f,%.2f)", 
                //           j, tlX, tlY, brX, brY, centerCam(0), centerCam(1), centerCam(2));
            }

            // ROS_INFO("[dynamicDetector]: Projected %zu 3D boxes to image plane (%d skipped behind camera)", 
            //          filteredDetectionResults.detections.size(), skippedBehindCamera);

            for (int i=0; i<int(this->yoloDetectionResults_.detections.size()); ++i){
                // Check bounds (should always be valid, but add safety check)
                if (i < 0 || i >= static_cast<int>(this->yoloDetectionResults_.detections.size())) {
                    // ROS_WARN("[dynamicDetector]: Invalid YOLO detection index %d (size=%zu), skipping", 
                    //          i, this->yoloDetectionResults_.detections.size());
                    continue;
                }
                
                int tlXTarget = int(this->yoloDetectionResults_.detections[i].bbox.center.x);
                int tlYTarget = int(this->yoloDetectionResults_.detections[i].bbox.center.y);
                int brXTarget = tlXTarget + int(this->yoloDetectionResults_.detections[i].bbox.size_x);
                int brYTarget = tlYTarget + int(this->yoloDetectionResults_.detections[i].bbox.size_y);

                cv::Rect bboxVis;
                bboxVis.x = tlXTarget;
                bboxVis.y = tlYTarget;
                bboxVis.height = brYTarget - tlYTarget;
                bboxVis.width = brXTarget - tlXTarget;
                cv::rectangle(this->detectedColorImage_, bboxVis, cv::Scalar(255, 0, 0), 5, 8, 0);

                // Define the text to be added
                std::string text = "dynamic";

                // Define the position for the text (above the bounding box)
                int fontFace = cv::FONT_HERSHEY_SIMPLEX;
                double fontScale = 1.0;
                int thickness = 2;
                int baseline;
                cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
                cv::Point textOrg(bboxVis.x, bboxVis.y - 10);  // 10 pixels above the bounding box

                // Add the text to the image
                cv::putText(this->detectedColorImage_, text, textOrg, fontFace, fontScale, cv::Scalar(255, 0, 0), thickness, 8);

                double bestIOU = 0.0;
                int bestIdx = -1;
                for (int j = 0; j < int(filteredDetectionResults.detections.size()); ++j) {
                    int tlX = int(filteredDetectionResults.detections[j].bbox.center.x);
                    int tlY = int(filteredDetectionResults.detections[j].bbox.center.y);
                    int brX = tlX + int(filteredDetectionResults.detections[j].bbox.size_x);
                    int brY = tlY + int(filteredDetectionResults.detections[j].bbox.size_y);

                    // check the IOU between yolo and projected bbox
                    double xOverlap = double(std::max(0, std::min(brX, brXTarget) - std::max(tlX, tlXTarget)));
                    double yOverlap = double(std::max(0, std::min(brY, brYTarget) - std::max(tlY, tlYTarget)));
                    double intersection = xOverlap * yOverlap;

                    // Calculate union area
                    double areaBox = double((brX - tlX) * (brY - tlY));
                    double areaBoxTarget = double((brXTarget - tlXTarget) * (brYTarget - tlYTarget));
                    double unionArea = areaBox + areaBoxTarget - intersection;

                    double IOU = (unionArea == 0) ? 0 : intersection / unionArea;
                    if (IOU > bestIOU){
                        bestIOU = IOU;
                        bestIdx = j;
                    }
                }

                // ROS_INFO("[dynamicDetector]: YOLO detection %d: bbox=(%d,%d,%d,%d), best match: 3D box %d, IOU: %.3f", 
                //          i, tlXTarget, tlYTarget, brXTarget, brYTarget, bestIdx, bestIOU);
                
                // Print projected boxes for debugging
                // if (filteredDetectionResults.detections.size() > 0) {
                //     ROS_INFO("[dynamicDetector]: Available projected boxes:");
                //     for (int j = 0; j < int(filteredDetectionResults.detections.size()); ++j) {
                //         int ptlX = int(filteredDetectionResults.detections[j].bbox.center.x);
                //         int ptlY = int(filteredDetectionResults.detections[j].bbox.center.y);
                //         int pbrX = ptlX + int(filteredDetectionResults.detections[j].bbox.size_x);
                //         int pbrY = ptlY + int(filteredDetectionResults.detections[j].bbox.size_y);
                //         ROS_INFO("[dynamicDetector]:   Box %d: tl=(%d,%d), br=(%d,%d)", j, ptlX, ptlY, pbrX, pbrY);
                //     }
                // } else {
                //     ROS_WARN("[dynamicDetector]: No projected boxes available for matching!");
                // }

                if (bestIOU > 0.0){
                    best3DBBoxForYOLO[i] = bestIdx;
                } else {
                    // ROS_WARN("[dynamicDetector]: YOLO detection %d matched with NO 3D box (IOU=0)", i);
                }
            }

            std::map<int, std::vector<int>> box3DToYolo;
            int matchedYoloCount = 0;
            for (int i = 0; i < int(best3DBBoxForYOLO.size()); ++i) {
                int idx3D = best3DBBoxForYOLO[i];
                if (idx3D >= 0 && idx3D < int(filteredBBoxesTemp.size())){
                    box3DToYolo[idx3D].push_back(i);
                    matchedYoloCount++;
                }
            }
            // ROS_INFO("[dynamicDetector]: Matched %d YOLO detections to 3D boxes", matchedYoloCount);

            std::vector<onboardDetector::box3D> newFilteredBBoxes;
            std::vector<std::vector<Eigen::Vector3d>> newFilteredPcClusters;
            std::vector<Eigen::Vector3d> newFilteredPcClusterCenters;
            std::vector<Eigen::Vector3d> newFilteredPcClusterStds;
            
            for (int idx3D = 0; idx3D < int(filteredBBoxesTemp.size()); ++idx3D) {
                auto it = box3DToYolo.find(idx3D);
                // *Case 1: No corresponding yolo box - skip it (only output YOLO-detected targets)
                if (it == box3DToYolo.end()) {
                    continue;  // Skip boxes without YOLO match
                }

                // Check bounds for all arrays
                if (idx3D < 0 || idx3D >= static_cast<int>(filteredBBoxesTemp.size()) ||
                    idx3D >= static_cast<int>(filteredPcClustersTemp.size()) ||
                    idx3D >= static_cast<int>(filteredPcClusterCentersTemp.size()) ||
                    idx3D >= static_cast<int>(filteredPcClusterStdsTemp.size())) {
                    // ROS_WARN("[dynamicDetector]: Invalid index %d for filtered arrays, skipping", idx3D);
                    continue;
                }

                std::vector<int> yoloIndices = it->second;
                // *Case 2: one yolo box corresponds to one 3D box
                if (yoloIndices.size() == 1) {
                    filteredBBoxesTemp[idx3D].is_dynamic = true;
                    filteredBBoxesTemp[idx3D].is_human = true;
                    newFilteredBBoxes.push_back(filteredBBoxesTemp[idx3D]);
                    newFilteredPcClusters.push_back(filteredPcClustersTemp[idx3D]);
                    newFilteredPcClusterCenters.push_back(filteredPcClusterCentersTemp[idx3D]);
                    newFilteredPcClusterStds.push_back(filteredPcClusterStdsTemp[idx3D]);
                // *Case 3: multiple yolo boxes correspond to one 3D box
                } else {
                    std::vector<Eigen::Vector3d> cloudCluster = filteredPcClustersTemp[idx3D];

                    // iterate to assign all points
                    int allowMargin = 0; // pixel 
                    std::vector<int> assignment(cloudCluster.size(), -1);
                    for (size_t i = 0; i < cloudCluster.size(); ++i){
                        Eigen::Vector3d ptWorld = cloudCluster[i];
                        Eigen::Vector3d ptCam = this->orientationColor_.inverse() * (ptWorld - this->positionColor_);

                        int u = (this->fxC_ * ptCam(0) + this->cxC_ * ptCam(2)) / ptCam(2);
                        int v = (this->fyC_ * ptCam(1) + this->cyC_ * ptCam(2)) / ptCam(2);

                        int closestDist = std::numeric_limits<int>::max();
                        for (int yidx : yoloIndices){
                            // Check bounds
                            if (yidx < 0 || yidx >= static_cast<int>(this->yoloDetectionResults_.detections.size())) {
                                // ROS_WARN("[dynamicDetector]: Invalid YOLO index %d, skipping", yidx);
                                continue;
                            }
                            
                            int XTarget = int(this->yoloDetectionResults_.detections[yidx].bbox.center.x);
                            int YTarget = int(this->yoloDetectionResults_.detections[yidx].bbox.center.y);
                            int XTargetWid = int(this->yoloDetectionResults_.detections[yidx].bbox.size_x);
                            int YTargetWid = int(this->yoloDetectionResults_.detections[yidx].bbox.size_y);
                            int xMin = XTarget;
                            int xMax = XTarget + XTargetWid;
                            int yMin = YTarget;
                            int yMax = YTarget + YTargetWid;

                            if (u >= xMin-allowMargin && u <= xMax+allowMargin && v >= yMin-allowMargin && v <= yMax+allowMargin) {
                                // Horizontal signed distance
                                int horizontalDistance = 0;
                                if (u < xMin) {
                                    horizontalDistance = xMin - u; // Outside on the left
                                } else if (u > xMax) {
                                    horizontalDistance = u - xMax; // Outside on the right
                                } else {
                                    horizontalDistance = std::max(xMin - u, u - xMax); // Inside horizontally
                                }

                                // Compute signed distance to the closest edge
                                int signedDistance;
                                if (u < xMin || u > xMax || v < yMin || v > yMax) {
                                    // Outside: Take the larger of horizontal or vertical distance
                                    signedDistance = horizontalDistance;
                                } else {
                                    // Inside: Take the negative of the minimum distance to any edge
                                    signedDistance = horizontalDistance;
                                }
          
                                int distance = signedDistance;
                                if (distance < closestDist){
                                    assignment[i] = yidx;
                                    closestDist = distance;
                                }
                            }
                        }
                    }

                    std::vector<bool> flag(cloudCluster.size(), false);
                    for (int yidx : yoloIndices){
                        std::vector<Eigen::Vector3d> subCloud;
                        for (size_t i = 0; i < cloudCluster.size(); ++i){
                            if (flag[i]){
                                continue;
                            }

                            if (assignment[i] == yidx){
                                subCloud.push_back(cloudCluster[i]);
                                flag[i] = true;
                            }
                        }
                        if (subCloud.size() != 0){
                            onboardDetector::box3D newBox;
                            Eigen::Vector3d center, stddev;
                            center = onboardDetector::computeCenter(subCloud);

                            double xMin = std::numeric_limits<double>::max(), xMax = std::numeric_limits<double>::lowest();
                            double yMin = std::numeric_limits<double>::max(), yMax = std::numeric_limits<double>::lowest();
                            double zMin = std::numeric_limits<double>::max(), zMax = std::numeric_limits<double>::lowest();

                            for (const auto &pt : subCloud) {
                                xMin = std::min(xMin, pt.x());
                                xMax = std::max(xMax, pt.x());
                                yMin = std::min(yMin, pt.y());
                                yMax = std::max(yMax, pt.y());
                                zMin = std::min(zMin, pt.z());
                                zMax = std::max(zMax, pt.z());
                            }
                            // create a new bounding box
                            newBox.x = (xMin + xMax) / 2.;
                            newBox.y = (yMin + yMax) / 2.;
                            newBox.z = (zMin + zMax) / 2.;
                            newBox.x_width = xMax - xMin;
                            newBox.y_width = yMax - yMin;
                            newBox.z_width = zMax - zMin;
                            if (newBox.x_width <= 0 || newBox.y_width <= 0 || newBox.z_width <= 0){
                                continue;
                            }

                            newBox.is_dynamic = true;
                            newBox.is_human = true;

                            stddev = onboardDetector::computeStd(subCloud, center);
                            newFilteredBBoxes.push_back(newBox);
                            newFilteredPcClusters.push_back(subCloud);
                            newFilteredPcClusterCenters.push_back(center);
                            newFilteredPcClusterStds.push_back(stddev);
                        }
                    }
                }
            }
            filteredBBoxesTemp = newFilteredBBoxes;
            filteredPcClustersTemp = newFilteredPcClusters;
            filteredPcClusterCentersTemp = newFilteredPcClusterCenters;
            filteredPcClusterStdsTemp = newFilteredPcClusterStds;
        }
        // Only output 3D boxes that match YOLO detections
        // Ensure all arrays have consistent sizes
        if (filteredBBoxesTemp.size() != filteredPcClustersTemp.size() ||
            filteredBBoxesTemp.size() != filteredPcClusterCentersTemp.size() ||
            filteredBBoxesTemp.size() != filteredPcClusterStdsTemp.size()) {
            // ROS_ERROR("[dynamicDetector]: Array size mismatch after filtering: boxes=%zu, clusters=%zu, centers=%zu, stds=%zu",
            //           filteredBBoxesTemp.size(), filteredPcClustersTemp.size(), 
            //           filteredPcClusterCentersTemp.size(), filteredPcClusterStdsTemp.size());
            // Clear all to prevent inconsistency
            filteredBBoxesTemp.clear();
            filteredPcClustersTemp.clear();
            filteredPcClusterCentersTemp.clear();
            filteredPcClusterStdsTemp.clear();
        }
        
        this->filteredBBoxes_ = filteredBBoxesTemp;
        this->filteredPcClusters_ = filteredPcClustersTemp;
        this->filteredPcClusterCenters_ = filteredPcClusterCentersTemp;
        this->filteredPcClusterStds_ = filteredPcClusterStdsTemp;
        
        // Note: filteredBBoxes_ contains current frame detections only
        // multiFrameFusion() will merge them with confirmed targets
    }

    void dynamicDetector::multiFrameFusion(){
        ros::Time currentTime = ros::Time::now();
        
        // Store current detections from filterLVBBoxes (before fusion)
        std::vector<onboardDetector::box3D> currentDetections = this->filteredBBoxes_;
        
        // Filter current detections: remove invalid boxes before processing
        std::vector<onboardDetector::box3D> filteredCurrentDetections;
        for (const auto& box : currentDetections) {
            // Validate box dimensions
            if (box.x_width <= 0 || box.y_width <= 0 || box.z_width <= 0) {
                continue;
            }
            // Check max object size
            if (box.x_width > this->maxObjectSize_(0) || 
                box.y_width > this->maxObjectSize_(1) || 
                box.z_width > this->maxObjectSize_(2)) {
                continue; // Skip boxes that are too large (likely obstacles)
            }
            // Check minimum size (too small might be noise)
            if (box.x_width < 0.2 || box.y_width < 0.2 || box.z_width < 0.2) {
                continue; // Skip boxes that are too small
            }
            // Check height (z position) - targets should be on ground level
            double groundHeight = 0.2; // ground height threshold
            double maxHeight = 3.0; // maximum reasonable height for targets
            if (box.z < -groundHeight || box.z > maxHeight) {
                continue; // Skip boxes outside reasonable height range
            }
            filteredCurrentDetections.push_back(box);
        }
        currentDetections = filteredCurrentDetections;
        
        // Merge nearby current detections before matching (to avoid matching nearby obstacles as separate targets)
        currentDetections = this->mergeNearbyTargets(currentDetections, this->targetMergeDistance_);
        
        // Match current detections with history
        std::vector<bool> currentMatched(currentDetections.size(), false);
        std::vector<bool> historyMatched(this->detectedTargetsHistory_.size(), false);
        
        // Step 1: Match current detections with existing targets
        for (size_t i = 0; i < currentDetections.size(); ++i) {
            double bestIOU = 0.0;
            int bestHistoryIdx = -1;
            
            for (size_t j = 0; j < this->detectedTargetsHistory_.size(); ++j) {
                if (historyMatched[j]) continue;
                
                // Validate history target box
                const auto& historyBox = this->detectedTargetsHistory_[j].box;
                if (historyBox.x_width <= 0 || historyBox.y_width <= 0 || historyBox.z_width <= 0) {
                    // ROS_WARN("[dynamicDetector]: Invalid history box at index %zu, skipping", j);
                    continue;
                }
                
                double IOU = this->calBoxIOU(currentDetections[i], this->detectedTargetsHistory_[j].box);
                if (IOU > bestIOU && IOU >= this->targetMatchIOU_) {
                    bestIOU = IOU;
                    bestHistoryIdx = static_cast<int>(j);
                }
            }
            
            if (bestHistoryIdx >= 0 && bestHistoryIdx < static_cast<int>(this->detectedTargetsHistory_.size()) &&
                bestHistoryIdx < static_cast<int>(historyMatched.size())) {
                // Update existing target
                DetectedTarget& target = this->detectedTargetsHistory_[bestHistoryIdx];
                target.detectionCount++;
                target.missCount = 0;
                target.lastSeen = currentTime;
                
                // Update box with weighted average (smooth the position)
                double alpha = 0.3; // smoothing factor
                target.box.x = alpha * currentDetections[i].x + (1.0 - alpha) * target.box.x;
                target.box.y = alpha * currentDetections[i].y + (1.0 - alpha) * target.box.y;
                target.box.z = alpha * currentDetections[i].z + (1.0 - alpha) * target.box.z;
                
                // Update size with weighted average
                target.box.x_width = alpha * currentDetections[i].x_width + (1.0 - alpha) * target.box.x_width;
                target.box.y_width = alpha * currentDetections[i].y_width + (1.0 - alpha) * target.box.y_width;
                target.box.z_width = alpha * currentDetections[i].z_width + (1.0 - alpha) * target.box.z_width;
                
                // Preserve other properties
                target.box.is_dynamic = currentDetections[i].is_dynamic;
                target.box.is_human = currentDetections[i].is_human;
                
                // Update confidence (increase with more detections, capped at 1.0)
                // Slower confidence growth to reduce false positives
                target.confidence = std::min(1.0, target.confidence + 0.1);
                
                currentMatched[i] = true;
                historyMatched[bestHistoryIdx] = true;
            } else {
                // New detection - add to history with very low initial confidence
                DetectedTarget newTarget;
                newTarget.box = currentDetections[i];
                newTarget.detectionCount = 1;
                newTarget.missCount = 0;
                newTarget.confidence = 0.1; // Very low initial confidence to reduce false positives
                newTarget.lastSeen = currentTime;
                this->detectedTargetsHistory_.push_back(newTarget);
            }
        }
        
        // Step 2: Update unmatched history targets (increase miss count, decrease confidence)
        // Re-check historyMatched size before accessing (may have changed if history was modified)
        size_t historySize = this->detectedTargetsHistory_.size();
        for (size_t i = 0; i < historySize; ++i) {
            if (i >= historyMatched.size()) {
                // Size mismatch detected, break to prevent crash
                break;
            }
            if (!historyMatched[i]) {
                // Additional bounds check before accessing
                if (i < this->detectedTargetsHistory_.size()) {
                    DetectedTarget& target = this->detectedTargetsHistory_[i];
                    target.missCount++;
                    target.confidence = std::max(0.0, target.confidence - this->confidenceDecay_);
                }
            }
        }
        
        // Step 3: Remove targets that have been missing for too long or have low confidence
        // Only remove unconfirmed targets (low confidence or not enough detections)
        // Confirmed targets are NEVER deleted once confirmed
        auto it = this->detectedTargetsHistory_.begin();
        while (it != this->detectedTargetsHistory_.end()) {
            // Keep confirmed targets permanently - never delete them
            // Stricter confirmation criteria: more frames AND higher confidence
            bool isConfirmed = (it->detectionCount >= this->minDetectionFrames_ && it->confidence >= 0.7);
            if (!isConfirmed && (it->missCount >= this->maxMissFrames_ || it->confidence <= 0.0)) {
                it = this->detectedTargetsHistory_.erase(it);
            } else {
                ++it;
            }
        }
        
        // Limit history size to prevent memory issues
        // NEVER remove confirmed targets, only remove unconfirmed targets
        const size_t maxHistorySize = 50;
        if (this->detectedTargetsHistory_.size() > maxHistorySize) {
            // Count confirmed targets
            size_t confirmedCount = 0;
            for (const auto& target : this->detectedTargetsHistory_) {
                if (target.detectionCount >= this->minDetectionFrames_ && target.confidence >= 0.7) {
                    confirmedCount++;
                }
            }
            
            // Only remove unconfirmed targets if there are too many total targets
            if (confirmedCount < maxHistorySize) {
                std::vector<DetectedTarget> unconfirmedTargets;
                std::vector<DetectedTarget> confirmedTargets;
                
                for (const auto& target : this->detectedTargetsHistory_) {
                    bool isConfirmed = (target.detectionCount >= this->minDetectionFrames_ && target.confidence >= 0.7);
                    if (isConfirmed) {
                        confirmedTargets.push_back(target);
                    } else {
                        unconfirmedTargets.push_back(target);
                    }
                }
                
                // Sort unconfirmed targets by confidence (lowest first)
                std::sort(unconfirmedTargets.begin(), unconfirmedTargets.end(),
                          [](const DetectedTarget& a, const DetectedTarget& b) {
                              return a.confidence < b.confidence;
                          });
                
                // Keep only enough unconfirmed targets to fill remaining slots
                size_t remainingSlots = maxHistorySize - confirmedCount;
                if (unconfirmedTargets.size() > remainingSlots) {
                    unconfirmedTargets.resize(remainingSlots);
                }
                
                // Combine confirmed and unconfirmed targets
                this->detectedTargetsHistory_.clear();
                this->detectedTargetsHistory_.insert(this->detectedTargetsHistory_.end(), 
                                                     confirmedTargets.begin(), confirmedTargets.end());
                this->detectedTargetsHistory_.insert(this->detectedTargetsHistory_.end(), 
                                                     unconfirmedTargets.begin(), unconfirmedTargets.end());
            }
            // If confirmed targets already exceed maxHistorySize, keep all confirmed targets
            // (This might cause memory growth, but confirmed targets are never deleted)
        }
        
        // Step 4: Build confirmed targets list (all confirmed targets)
        // Accumulate confirmed targets, don't clear existing ones
        // Get all confirmed targets from history
        std::vector<onboardDetector::box3D> confirmedFromHistory;
        for (const auto& target : this->detectedTargetsHistory_) {
            // Stricter confirmation criteria: more frames AND higher confidence
            if (target.detectionCount >= this->minDetectionFrames_ && target.confidence >= 0.7) {
                // Validate box before adding
                if (target.box.x_width > 0 && target.box.y_width > 0 && target.box.z_width > 0) {
                    // Additional filtering: size constraints and position validation
                    // Check max object size
                    if (target.box.x_width <= this->maxObjectSize_(0) && 
                        target.box.y_width <= this->maxObjectSize_(1) && 
                        target.box.z_width <= this->maxObjectSize_(2)) {
                        // Check minimum size (too small might be noise)
                        if (target.box.x_width >= 0.2 && target.box.y_width >= 0.2 && target.box.z_width >= 0.2) {
                            // Check height (z position) - targets should be on ground level
                            // Allow some tolerance for UAV height variation
                            double groundHeight = 0.2; // ground height threshold
                            double maxHeight = 3.0; // maximum reasonable height for targets
                            if (target.box.z >= -groundHeight && target.box.z <= maxHeight) {
                                confirmedFromHistory.push_back(target.box);
                            }
                        }
                    }
                }
            }
        }
        
        // Merge nearby confirmed targets from history first
        confirmedFromHistory = this->mergeNearbyTargets(confirmedFromHistory, this->targetMergeDistance_);
        
        // Update confirmed targets list
        // Confirmed targets are permanently saved, but their positions should be updated when detected
        // Start with existing confirmed boxes (these are permanently saved)
        std::vector<onboardDetector::box3D> mergedConfirmedBBoxes = this->confirmedBBoxes_;
        
        // Update existing confirmed boxes with new positions from history, or add new ones
        for (const auto& newBox : confirmedFromHistory) {
            bool isUpdated = false;
            // Check if this box matches an existing confirmed box (same target)
            for (auto& existingBox : mergedConfirmedBBoxes) {
                double IOU = this->calBoxIOU(newBox, existingBox);
                double distance = this->calBoxDistance(newBox, existingBox);
                // If IOU > 0.3 OR distance is close, consider it the same target and update position
                if (IOU > 0.3 || distance <= this->targetMergeDistance_) {
                    // Update position with new detection (same target, updated position)
                    existingBox.x = newBox.x;
                    existingBox.y = newBox.y;
                    existingBox.z = newBox.z;
                    existingBox.x_width = newBox.x_width;
                    existingBox.y_width = newBox.y_width;
                    existingBox.z_width = newBox.z_width;
                    existingBox.is_dynamic = newBox.is_dynamic;
                    existingBox.is_human = newBox.is_human;
                    isUpdated = true;
                    break;
                }
            }
            // If not matched to existing box, add as new confirmed target
            if (!isUpdated) {
                mergedConfirmedBBoxes.push_back(newBox);
            }
        }
        
        // Confirmed targets are permanently saved - never remove them even if temporarily missing from history
        // All existing confirmed boxes are kept, with updated positions when detected
        
        // Merge nearby targets in final list to ensure no duplicates
        mergedConfirmedBBoxes = this->mergeNearbyTargets(mergedConfirmedBBoxes, this->targetMergeDistance_);
        
        this->confirmedBBoxes_ = mergedConfirmedBBoxes;
        
        // Update filteredBBoxes_ with all confirmed targets (accumulated, not cleared)
        this->filteredBBoxes_ = this->confirmedBBoxes_;
        
        // ROS_DEBUG("[dynamicDetector]: Multi-frame fusion: %zu current detections, %zu history targets, %zu confirmed targets",
        //           currentDetections.size(), this->detectedTargetsHistory_.size(), this->confirmedBBoxes_.size());
    }



    double dynamicDetector::calBoxIOU(const onboardDetector::box3D& box1, const onboardDetector::box3D& box2, bool ignoreZmin){
        // Validate box dimensions
        if (box1.x_width <= 0 || box1.y_width <= 0 || box1.z_width <= 0 ||
            box2.x_width <= 0 || box2.y_width <= 0 || box2.z_width <= 0) {
            return 0.0;
        }
        
        double box1Volume = box1.x_width * box1.y_width * box1.z_width;
        double box2Volume = box2.x_width * box2.y_width * box2.z_width;

        double l1Y = box1.y+box1.y_width/2.-(box2.y-box2.y_width/2.);
        double l2Y = box2.y+box2.y_width/2.-(box1.y-box1.y_width/2.);
        double l1X = box1.x+box1.x_width/2.-(box2.x-box2.x_width/2.);
        double l2X = box2.x+box2.x_width/2.-(box1.x-box1.x_width/2.);
        double l1Z = box1.z+box1.z_width/2.-(box2.z-box2.z_width/2.);
        double l2Z = box2.z+box2.z_width/2.-(box1.z-box1.z_width/2.);
        
        if (ignoreZmin){
            // modify box1 and box2 volumn based on the maximum lower z of two
            double zmin = std::max(box1.z - box1.z_width/2., box2.z - box2.z_width/2.);
            double zWidth1 = box1.z_width/2. + (box1.z - zmin);
            double zWidth2 = box2.z_width/2. + (box2.z - zmin);
            if (zWidth1 <= 0 || zWidth2 <= 0) {
                return 0.0;
            }
            box1Volume = box1.x_width * box1.y_width * zWidth1;
            box2Volume = box2.x_width * box2.y_width * zWidth2;

            l1Z = box1.z+box1.z_width/2. - zmin;
            l2Z = box2.z+box2.z_width/2. - zmin;
        }
        
        double overlapX = std::min( l1X , l2X );
        double overlapY = std::min( l1Y , l2Y );
        double overlapZ = std::min( l1Z , l2Z );
       
        if (std::max(l1X, l2X)<=std::max(box1.x_width,box2.x_width)){ 
            overlapX = std::min(box1.x_width, box2.x_width);
        }
        if (std::max(l1Y, l2Y)<=std::max(box1.y_width,box2.y_width)){ 
            overlapY = std::min(box1.y_width, box2.y_width);
        }
        if (std::max(l1Z, l2Z)<=std::max(box1.z_width,box2.z_width)){ 
            overlapZ = std::min(box1.z_width, box2.z_width);
        }

        double overlapVolume = overlapX * overlapY *  overlapZ;
        
        // Check for division by zero
        double unionVolume = box1Volume + box2Volume - overlapVolume;
        if (unionVolume <= 0) {
            return 0.0;
        }
        
        double IOU = overlapVolume / unionVolume;
        
        // D-IOU
        if (overlapX<=0 || overlapY<=0 ||overlapZ<=0){
            IOU = 0;
        }
        
        // Validate result
        if (std::isnan(IOU) || std::isinf(IOU)) {
            // ROS_WARN("[dynamicDetector]: Invalid IOU value: %f, returning 0", IOU);
            return 0.0;
        }
        
        return IOU;
    }

    double dynamicDetector::calBoxDistance(const onboardDetector::box3D& box1, const onboardDetector::box3D& box2){
        // Calculate Euclidean distance between box centers
        double dx = box1.x - box2.x;
        double dy = box1.y - box2.y;
        double dz = box1.z - box2.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    std::vector<onboardDetector::box3D> dynamicDetector::mergeNearbyTargets(const std::vector<onboardDetector::box3D>& boxes, double mergeDistanceThreshold){
        if (boxes.empty()) {
            return boxes;
        }

        std::vector<onboardDetector::box3D> mergedBoxes;
        std::vector<bool> merged(boxes.size(), false);

        for (size_t i = 0; i < boxes.size(); ++i) {
            if (merged[i]) continue;
            
            // Start with box i
            onboardDetector::box3D mergedBox = boxes[i];
            std::vector<size_t> toMerge = {i};
            
            // Find all nearby boxes to merge
            for (size_t j = i + 1; j < boxes.size(); ++j) {
                if (merged[j]) continue;
                
                double distance = this->calBoxDistance(boxes[i], boxes[j]);
                if (distance <= mergeDistanceThreshold) {
                    toMerge.push_back(j);
                    merged[j] = true;
                }
            }
            
            // Merge multiple boxes into one
            if (toMerge.size() > 1) {
                // Calculate weighted average center (can be improved with confidence weighting)
                double sumX = 0, sumY = 0, sumZ = 0;
                double sumXWidth = 0, sumYWidth = 0, sumZWidth = 0;
                
                for (size_t idx : toMerge) {
                    // Validate index before accessing
                    if (idx >= boxes.size()) {
                        continue; // Skip invalid index
                    }
                    sumX += boxes[idx].x;
                    sumY += boxes[idx].y;
                    sumZ += boxes[idx].z;
                    sumXWidth += boxes[idx].x_width;
                    sumYWidth += boxes[idx].y_width;
                    sumZWidth += boxes[idx].z_width;
                }
                
                mergedBox.x = sumX / toMerge.size();
                mergedBox.y = sumY / toMerge.size();
                mergedBox.z = sumZ / toMerge.size();
                
                // Take maximum size to encompass all merged boxes
                mergedBox.x_width = sumXWidth / toMerge.size();
                mergedBox.y_width = sumYWidth / toMerge.size();
                mergedBox.z_width = sumZWidth / toMerge.size();
                
                // Find the bounding box that encompasses all merged boxes
                double xMin = mergedBox.x - mergedBox.x_width / 2.0;
                double xMax = mergedBox.x + mergedBox.x_width / 2.0;
                double yMin = mergedBox.y - mergedBox.y_width / 2.0;
                double yMax = mergedBox.y + mergedBox.y_width / 2.0;
                double zMin = mergedBox.z - mergedBox.z_width / 2.0;
                double zMax = mergedBox.z + mergedBox.z_width / 2.0;
                
                for (size_t idx : toMerge) {
                    // Validate index before accessing
                    if (idx >= boxes.size()) {
                        continue; // Skip invalid index
                    }
                    xMin = std::min(xMin, boxes[idx].x - boxes[idx].x_width / 2.0);
                    xMax = std::max(xMax, boxes[idx].x + boxes[idx].x_width / 2.0);
                    yMin = std::min(yMin, boxes[idx].y - boxes[idx].y_width / 2.0);
                    yMax = std::max(yMax, boxes[idx].y + boxes[idx].y_width / 2.0);
                    zMin = std::min(zMin, boxes[idx].z - boxes[idx].z_width / 2.0);
                    zMax = std::max(zMax, boxes[idx].z + boxes[idx].z_width / 2.0);
                }
                
                mergedBox.x = (xMin + xMax) / 2.0;
                mergedBox.y = (yMin + yMax) / 2.0;
                mergedBox.z = (zMin + zMax) / 2.0;
                mergedBox.x_width = xMax - xMin;
                mergedBox.y_width = yMax - yMin;
                mergedBox.z_width = zMax - zMin;
            }
            
            mergedBoxes.push_back(mergedBox);
            merged[i] = true;
        }
        
        return mergedBoxes;
    }

    void dynamicDetector::transformBBox(const Eigen::Vector3d& center, const Eigen::Vector3d& size, const Eigen::Vector3d& position, const Eigen::Matrix3d& orientation,
                                               Eigen::Vector3d& newCenter, Eigen::Vector3d& newSize){
        double x = center(0); 
        double y = center(1);
        double z = center(2);
        double xWidth = size(0);
        double yWidth = size(1);
        double zWidth = size(2);

        // get 8 bouding boxes coordinates in the camera frame
        Eigen::Vector3d p1 (x+xWidth/2.0, y+yWidth/2.0, z+zWidth/2.0);
        Eigen::Vector3d p2 (x+xWidth/2.0, y+yWidth/2.0, z-zWidth/2.0);
        Eigen::Vector3d p3 (x+xWidth/2.0, y-yWidth/2.0, z+zWidth/2.0);
        Eigen::Vector3d p4 (x+xWidth/2.0, y-yWidth/2.0, z-zWidth/2.0);
        Eigen::Vector3d p5 (x-xWidth/2.0, y+yWidth/2.0, z+zWidth/2.0);
        Eigen::Vector3d p6 (x-xWidth/2.0, y+yWidth/2.0, z-zWidth/2.0);
        Eigen::Vector3d p7 (x-xWidth/2.0, y-yWidth/2.0, z+zWidth/2.0);
        Eigen::Vector3d p8 (x-xWidth/2.0, y-yWidth/2.0, z-zWidth/2.0);

        // transform 8 points to the map coordinate frame
        Eigen::Vector3d p1m = orientation * p1 + position;
        Eigen::Vector3d p2m = orientation * p2 + position;
        Eigen::Vector3d p3m = orientation * p3 + position;
        Eigen::Vector3d p4m = orientation * p4 + position;
        Eigen::Vector3d p5m = orientation * p5 + position;
        Eigen::Vector3d p6m = orientation * p6 + position;
        Eigen::Vector3d p7m = orientation * p7 + position;
        Eigen::Vector3d p8m = orientation * p8 + position;
        std::vector<Eigen::Vector3d> pointsMap {p1m, p2m, p3m, p4m, p5m, p6m, p7m, p8m};

        // find max min in x, y, z directions
        double xmin=p1m(0); double xmax=p1m(0); 
        double ymin=p1m(1); double ymax=p1m(1);
        double zmin=p1m(2); double zmax=p1m(2);
        for (Eigen::Vector3d pm : pointsMap){
            if (pm(0) < xmin){xmin = pm(0);}
            if (pm(0) > xmax){xmax = pm(0);}
            if (pm(1) < ymin){ymin = pm(1);}
            if (pm(1) > ymax){ymax = pm(1);}
            if (pm(2) < zmin){zmin = pm(2);}
            if (pm(2) > zmax){zmax = pm(2);}
        }
        newCenter(0) = (xmin + xmax)/2.0;
        newCenter(1) = (ymin + ymax)/2.0;
        newCenter(2) = (zmin + zmax)/2.0;
        newSize(0) = xmax - xmin;
        newSize(1) = ymax - ymin;
        newSize(2) = zmax - zmin;
    }

    int dynamicDetector::getBestOverlapBBox(const onboardDetector::box3D& currBBox, const std::vector<onboardDetector::box3D>& targetBBoxes, double& bestIOU){
        bestIOU = 0.0;
        int bestIOUIdx = -1; // no match
        for (size_t i=0; i<targetBBoxes.size(); ++i){
            onboardDetector::box3D targetBBox = targetBBoxes[i];
            double IOU = this->calBoxIOU(currBBox, targetBBox);
            if (IOU > bestIOU){
                bestIOU = IOU;
                bestIOUIdx = i;
            }
        }
        return bestIOUIdx;
    }

    // visualization functions
    void dynamicDetector::publishColorImages(){
        sensor_msgs::ImagePtr detectedColorImgMsg = cv_bridge::CvImage(std_msgs::Header(), "rgb8", this->detectedColorImage_).toImageMsg();
        this->detectedColorImgPub_.publish(detectedColorImgMsg);
    }

    void dynamicDetector::publish3dBox(const std::vector<box3D>& boxes,
                                   const ros::Publisher& publisher,
                                   double r, double g, double b){
        visualization_msgs::MarkerArray markers;

        for (size_t i = 0; i < boxes.size(); i++)
        {
            visualization_msgs::Marker line;
            line.header.frame_id = "world";
            line.ns = "box3D";
            line.id = i;
            line.type = visualization_msgs::Marker::LINE_LIST;
            line.action = visualization_msgs::Marker::ADD;
            line.scale.x = 0.06;
            line.color.r = r;
            line.color.g = g;
            line.color.b = b;
            line.color.a = 1.0;
            line.lifetime = ros::Duration(0.05);
            line.pose.orientation.x = 0.0;
            line.pose.orientation.y = 0.0;
            line.pose.orientation.z = 0.0;
            line.pose.orientation.w = 1.0;
            line.pose.position.x = boxes[i].x;
            line.pose.position.y = boxes[i].y;
            double x_width = boxes[i].x_width;
            double y_width = boxes[i].y_width;

            double top = boxes[i].z + boxes[i].z_width / 2.0;
            double z_width = top / 2.0;
            line.pose.position.z = z_width; 

            geometry_msgs::Point corner[8];
            corner[0].x = -x_width / 2.0; corner[0].y = -y_width / 2.0; corner[0].z = -z_width;
            corner[1].x = -x_width / 2.0; corner[1].y =  y_width / 2.0; corner[1].z = -z_width;
            corner[2].x =  x_width / 2.0; corner[2].y =  y_width / 2.0; corner[2].z = -z_width;
            corner[3].x =  x_width / 2.0; corner[3].y = -y_width / 2.0; corner[3].z = -z_width;

            corner[4].x = -x_width / 2.0; corner[4].y = -y_width / 2.0; corner[4].z =  z_width;
            corner[5].x = -x_width / 2.0; corner[5].y =  y_width / 2.0; corner[5].z =  z_width;
            corner[6].x =  x_width / 2.0; corner[6].y =  y_width / 2.0; corner[6].z =  z_width;
            corner[7].x =  x_width / 2.0; corner[7].y = -y_width / 2.0; corner[7].z =  z_width;

            int edgeIdx[12][2] = {
                {0,1}, {1,2}, {2,3}, {3,0},  
                {4,5}, {5,6}, {6,7}, {7,4},  
                {0,4}, {1,5}, {2,6}, {3,7}   
            };

            for (int e = 0; e < 12; e++)
            {
                line.points.push_back(corner[edgeIdx[e][0]]);
                line.points.push_back(corner[edgeIdx[e][1]]);
            }

            markers.markers.push_back(line);
        }

        publisher.publish(markers);
    }

    void dynamicDetector::publishTargetIdLabels(const std::vector<onboardDetector::box3D>& boxes){
        visualization_msgs::MarkerArray markers;

        // First, delete all old markers (up to a reasonable limit)
        const size_t maxOldMarkers = 100;
        for (size_t i = boxes.size(); i < maxOldMarkers; i++) {
            visualization_msgs::Marker deleteMarker;
            deleteMarker.header.frame_id = "world";
            deleteMarker.header.stamp = ros::Time::now();
            deleteMarker.ns = "target_id_labels";
            deleteMarker.id = i;
            deleteMarker.action = visualization_msgs::Marker::DELETE;
            markers.markers.push_back(deleteMarker);
        }

        // Then, add new markers for current boxes
        for (size_t i = 0; i < boxes.size(); i++)
        {
            visualization_msgs::Marker textMarker;
            textMarker.header.frame_id = "world";
            textMarker.header.stamp = ros::Time::now();
            textMarker.ns = "target_id_labels";
            textMarker.id = i;
            textMarker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
            textMarker.action = visualization_msgs::Marker::ADD;
            
            // Position: above the box center
            textMarker.pose.position.x = boxes[i].x;
            textMarker.pose.position.y = boxes[i].y;
            textMarker.pose.position.z = boxes[i].z + boxes[i].z_width / 2.0 + 0.5;  // Above the box
            
            textMarker.pose.orientation.x = 0.0;
            textMarker.pose.orientation.y = 0.0;
            textMarker.pose.orientation.z = 0.0;
            textMarker.pose.orientation.w = 1.0;
            
            // Text content: target ID (starting from 1)
            textMarker.text = std::to_string(i + 1);
            
            // Text properties
            textMarker.scale.z = 0.5;  // Text height
            textMarker.color.r = 1.0;  // Red color
            textMarker.color.g = 0.0;
            textMarker.color.b = 0.0;
            textMarker.color.a = 1.0;
            textMarker.lifetime = ros::Duration(0.1);

            markers.markers.push_back(textMarker);
        }

        this->targetIdLabelsPub_.publish(markers);
    }

    void dynamicDetector::publishConfirmedTargets(){
        onboard_detector::TargetBoxArray targetArray;
        targetArray.header.stamp = ros::Time::now();
        targetArray.header.frame_id = "world";
        
        // Create a local copy to avoid race conditions if multiFrameFusion modifies confirmedBBoxes_ during iteration
        std::vector<onboardDetector::box3D> confirmedBBoxesCopy = this->confirmedBBoxes_;
        
        // Convert confirmed boxes to TargetBox3D messages
        for (size_t i = 0; i < confirmedBBoxesCopy.size(); ++i) {
            const auto& box = confirmedBBoxesCopy[i];
            
            // Validate box before processing
            if (box.x_width <= 0 || box.y_width <= 0 || box.z_width <= 0) {
                continue; // Skip invalid boxes
            }
            
            onboard_detector::TargetBox3D targetBox;
            
            // Position
            targetBox.x = box.x;
            targetBox.y = box.y;
            targetBox.z = box.z;
            
            // Size
            targetBox.x_width = box.x_width;
            targetBox.y_width = box.y_width;
            targetBox.z_width = box.z_width;
            
            // ID (use index + 1 as target ID, or use box.id if available)
            targetBox.id = (box.id > 0) ? box.id : (i + 1);
            
            targetArray.targets.push_back(targetBox);
        }
        
        this->confirmedTargetsPub_.publish(targetArray);
    }

    void dynamicDetector::publishLidarClusters(){
        sensor_msgs::PointCloud2 lidarClustersMsg;
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr colored_cloud(new pcl::PointCloud<pcl::PointXYZRGB>());
        for (size_t i=0; i<this->lidarClusters_.size(); ++i){
            onboardDetector::Cluster & cluster = this->lidarClusters_[i];
            
            // Check if cluster points is valid
            if (cluster.points == nullptr || cluster.points->empty()) {
                continue;
            }

            std_msgs::ColorRGBA color;
            srand(cluster.cluster_id);
            color.r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            color.g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            color.b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

            for (size_t j=0; j<cluster.points->size(); ++j){
                pcl::PointXYZRGB point;
                const pcl::PointXYZ & pt = cluster.points->at(j);
                point.x = pt.x;
                point.y = pt.y;
                point.z = pt.z;
                point.r = color.r * 255;
                point.g = color.g * 255;
                point.b = color.b * 255;
                colored_cloud->push_back(point);
            }
        }
        pcl::toROSMsg(*colored_cloud, lidarClustersMsg);
        lidarClustersMsg.header.frame_id = "world";
        lidarClustersMsg.header.stamp = ros::Time::now();
        this->lidarClustersPub_.publish(lidarClustersMsg);
    }

    // user functions
    void dynamicDetector::getDynamicObstacles(std::vector<onboardDetector::box3D>& incomeDynamicBBoxes, const Eigen::Vector3d &robotSize){
        incomeDynamicBBoxes.clear();
        // use filteredBBoxes_ which contains lidar+yolo detection results
        for (int i=0; i<int(this->filteredBBoxes_.size()); i++){
            onboardDetector::box3D box = this->filteredBBoxes_[i];
            box.x_width += robotSize(0);
            box.y_width += robotSize(1);
            box.z_width += robotSize(2);
            incomeDynamicBBoxes.push_back(box);
        }
    }

}
