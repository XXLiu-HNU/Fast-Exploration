;; Auto-generated. Do not edit!


(when (boundp 'decomp_ros_msgs::EllipsoidArray)
  (if (not (find-package "DECOMP_ROS_MSGS"))
    (make-package "DECOMP_ROS_MSGS"))
  (shadow 'EllipsoidArray (find-package "DECOMP_ROS_MSGS")))
(unless (find-package "DECOMP_ROS_MSGS::ELLIPSOIDARRAY")
  (make-package "DECOMP_ROS_MSGS::ELLIPSOIDARRAY"))

(in-package "ROS")
;;//! \htmlinclude EllipsoidArray.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass decomp_ros_msgs::EllipsoidArray
  :super ros::object
  :slots (_header _ellipsoids ))

(defmethod decomp_ros_msgs::EllipsoidArray
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:ellipsoids __ellipsoids) ())
    )
   (send-super :init)
   (setq _header __header)
   (setq _ellipsoids __ellipsoids)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:ellipsoids
   (&rest __ellipsoids)
   (if (keywordp (car __ellipsoids))
       (send* _ellipsoids __ellipsoids)
     (progn
       (if __ellipsoids (setq _ellipsoids (car __ellipsoids)))
       _ellipsoids)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; decomp_ros_msgs/Ellipsoid[] _ellipsoids
    (apply #'+ (send-all _ellipsoids :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; decomp_ros_msgs/Ellipsoid[] _ellipsoids
     (write-long (length _ellipsoids) s)
     (dolist (elem _ellipsoids)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; decomp_ros_msgs/Ellipsoid[] _ellipsoids
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _ellipsoids (let (r) (dotimes (i n) (push (instance decomp_ros_msgs::Ellipsoid :init) r)) r))
     (dolist (elem- _ellipsoids)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get decomp_ros_msgs::EllipsoidArray :md5sum-) "e2c31e58d2b4b09679be4a3c12fffb19")
(setf (get decomp_ros_msgs::EllipsoidArray :datatype-) "decomp_ros_msgs/EllipsoidArray")
(setf (get decomp_ros_msgs::EllipsoidArray :definition-)
      "Header header
Ellipsoid[] ellipsoids

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: decomp_ros_msgs/Ellipsoid
float64[3] d
float64[9] E

")



(provide :decomp_ros_msgs/EllipsoidArray "e2c31e58d2b4b09679be4a3c12fffb19")


