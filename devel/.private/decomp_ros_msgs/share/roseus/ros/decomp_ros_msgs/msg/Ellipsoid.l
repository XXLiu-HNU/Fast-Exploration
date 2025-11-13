;; Auto-generated. Do not edit!


(when (boundp 'decomp_ros_msgs::Ellipsoid)
  (if (not (find-package "DECOMP_ROS_MSGS"))
    (make-package "DECOMP_ROS_MSGS"))
  (shadow 'Ellipsoid (find-package "DECOMP_ROS_MSGS")))
(unless (find-package "DECOMP_ROS_MSGS::ELLIPSOID")
  (make-package "DECOMP_ROS_MSGS::ELLIPSOID"))

(in-package "ROS")
;;//! \htmlinclude Ellipsoid.msg.html


(defclass decomp_ros_msgs::Ellipsoid
  :super ros::object
  :slots (_d _E ))

(defmethod decomp_ros_msgs::Ellipsoid
  (:init
   (&key
    ((:d __d) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:E __E) (make-array 9 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _d __d)
   (setq _E __E)
   self)
  (:d
   (&optional __d)
   (if __d (setq _d __d)) _d)
  (:E
   (&optional __E)
   (if __E (setq _E __E)) _E)
  (:serialization-length
   ()
   (+
    ;; float64[3] _d
    (* 8    3)
    ;; float64[9] _E
    (* 8    9)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[3] _d
     (dotimes (i 3)
       (sys::poke (elt _d i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[9] _E
     (dotimes (i 9)
       (sys::poke (elt _E i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[3] _d
   (dotimes (i (length _d))
     (setf (elt _d i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[9] _E
   (dotimes (i (length _E))
     (setf (elt _E i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;;
   self)
  )

(setf (get decomp_ros_msgs::Ellipsoid :md5sum-) "56675b593d9a5da51b91765fa8f29c87")
(setf (get decomp_ros_msgs::Ellipsoid :datatype-) "decomp_ros_msgs/Ellipsoid")
(setf (get decomp_ros_msgs::Ellipsoid :definition-)
      "float64[3] d
float64[9] E

")



(provide :decomp_ros_msgs/Ellipsoid "56675b593d9a5da51b91765fa8f29c87")


