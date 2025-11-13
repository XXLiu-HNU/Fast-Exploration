;; Auto-generated. Do not edit!


(when (boundp 'decomp_ros_msgs::PolyhedronArray)
  (if (not (find-package "DECOMP_ROS_MSGS"))
    (make-package "DECOMP_ROS_MSGS"))
  (shadow 'PolyhedronArray (find-package "DECOMP_ROS_MSGS")))
(unless (find-package "DECOMP_ROS_MSGS::POLYHEDRONARRAY")
  (make-package "DECOMP_ROS_MSGS::POLYHEDRONARRAY"))

(in-package "ROS")
;;//! \htmlinclude PolyhedronArray.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass decomp_ros_msgs::PolyhedronArray
  :super ros::object
  :slots (_header _polyhedrons ))

(defmethod decomp_ros_msgs::PolyhedronArray
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:polyhedrons __polyhedrons) ())
    )
   (send-super :init)
   (setq _header __header)
   (setq _polyhedrons __polyhedrons)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:polyhedrons
   (&rest __polyhedrons)
   (if (keywordp (car __polyhedrons))
       (send* _polyhedrons __polyhedrons)
     (progn
       (if __polyhedrons (setq _polyhedrons (car __polyhedrons)))
       _polyhedrons)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; decomp_ros_msgs/Polyhedron[] _polyhedrons
    (apply #'+ (send-all _polyhedrons :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; decomp_ros_msgs/Polyhedron[] _polyhedrons
     (write-long (length _polyhedrons) s)
     (dolist (elem _polyhedrons)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; decomp_ros_msgs/Polyhedron[] _polyhedrons
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _polyhedrons (let (r) (dotimes (i n) (push (instance decomp_ros_msgs::Polyhedron :init) r)) r))
     (dolist (elem- _polyhedrons)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get decomp_ros_msgs::PolyhedronArray :md5sum-) "ff07031dce96f472bf57a9bfa0a84d0a")
(setf (get decomp_ros_msgs::PolyhedronArray :datatype-) "decomp_ros_msgs/PolyhedronArray")
(setf (get decomp_ros_msgs::PolyhedronArray :definition-)
      "Header header
Polyhedron[] polyhedrons

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
MSG: decomp_ros_msgs/Polyhedron
geometry_msgs/Point[] points
geometry_msgs/Point[] normals #norm is an outer vector

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :decomp_ros_msgs/PolyhedronArray "ff07031dce96f472bf57a9bfa0a84d0a")


