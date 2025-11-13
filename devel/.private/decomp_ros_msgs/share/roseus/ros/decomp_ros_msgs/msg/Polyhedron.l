;; Auto-generated. Do not edit!


(when (boundp 'decomp_ros_msgs::Polyhedron)
  (if (not (find-package "DECOMP_ROS_MSGS"))
    (make-package "DECOMP_ROS_MSGS"))
  (shadow 'Polyhedron (find-package "DECOMP_ROS_MSGS")))
(unless (find-package "DECOMP_ROS_MSGS::POLYHEDRON")
  (make-package "DECOMP_ROS_MSGS::POLYHEDRON"))

(in-package "ROS")
;;//! \htmlinclude Polyhedron.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass decomp_ros_msgs::Polyhedron
  :super ros::object
  :slots (_points _normals ))

(defmethod decomp_ros_msgs::Polyhedron
  (:init
   (&key
    ((:points __points) ())
    ((:normals __normals) ())
    )
   (send-super :init)
   (setq _points __points)
   (setq _normals __normals)
   self)
  (:points
   (&rest __points)
   (if (keywordp (car __points))
       (send* _points __points)
     (progn
       (if __points (setq _points (car __points)))
       _points)))
  (:normals
   (&rest __normals)
   (if (keywordp (car __normals))
       (send* _normals __normals)
     (progn
       (if __normals (setq _normals (car __normals)))
       _normals)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point[] _points
    (apply #'+ (send-all _points :serialization-length)) 4
    ;; geometry_msgs/Point[] _normals
    (apply #'+ (send-all _normals :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point[] _points
     (write-long (length _points) s)
     (dolist (elem _points)
       (send elem :serialize s)
       )
     ;; geometry_msgs/Point[] _normals
     (write-long (length _normals) s)
     (dolist (elem _normals)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point[] _points
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _points (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _points)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; geometry_msgs/Point[] _normals
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _normals (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _normals)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get decomp_ros_msgs::Polyhedron :md5sum-) "30e67f500a403ad4875ae4600d46dde5")
(setf (get decomp_ros_msgs::Polyhedron :datatype-) "decomp_ros_msgs/Polyhedron")
(setf (get decomp_ros_msgs::Polyhedron :definition-)
      "geometry_msgs/Point[] points
geometry_msgs/Point[] normals #norm is an outer vector

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :decomp_ros_msgs/Polyhedron "30e67f500a403ad4875ae4600d46dde5")


