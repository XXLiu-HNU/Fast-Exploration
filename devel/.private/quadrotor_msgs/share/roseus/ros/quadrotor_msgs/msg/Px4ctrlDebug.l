;; Auto-generated. Do not edit!


(when (boundp 'quadrotor_msgs::Px4ctrlDebug)
  (if (not (find-package "QUADROTOR_MSGS"))
    (make-package "QUADROTOR_MSGS"))
  (shadow 'Px4ctrlDebug (find-package "QUADROTOR_MSGS")))
(unless (find-package "QUADROTOR_MSGS::PX4CTRLDEBUG")
  (make-package "QUADROTOR_MSGS::PX4CTRLDEBUG"))

(in-package "ROS")
;;//! \htmlinclude Px4ctrlDebug.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass quadrotor_msgs::Px4ctrlDebug
  :super ros::object
  :slots (_header _des_v_x _des_v_y _des_v_z _fb_a_x _fb_a_y _fb_a_z _des_a_x _des_a_y _des_a_z _des_q_x _des_q_y _des_q_z _des_q_w _des_thr _hover_percentage _thr_scale_compensate _voltage _err_axisang_x _err_axisang_y _err_axisang_z _err_axisang_ang _fb_rate_x _fb_rate_y _fb_rate_z ))

(defmethod quadrotor_msgs::Px4ctrlDebug
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:des_v_x __des_v_x) 0.0)
    ((:des_v_y __des_v_y) 0.0)
    ((:des_v_z __des_v_z) 0.0)
    ((:fb_a_x __fb_a_x) 0.0)
    ((:fb_a_y __fb_a_y) 0.0)
    ((:fb_a_z __fb_a_z) 0.0)
    ((:des_a_x __des_a_x) 0.0)
    ((:des_a_y __des_a_y) 0.0)
    ((:des_a_z __des_a_z) 0.0)
    ((:des_q_x __des_q_x) 0.0)
    ((:des_q_y __des_q_y) 0.0)
    ((:des_q_z __des_q_z) 0.0)
    ((:des_q_w __des_q_w) 0.0)
    ((:des_thr __des_thr) 0.0)
    ((:hover_percentage __hover_percentage) 0.0)
    ((:thr_scale_compensate __thr_scale_compensate) 0.0)
    ((:voltage __voltage) 0.0)
    ((:err_axisang_x __err_axisang_x) 0.0)
    ((:err_axisang_y __err_axisang_y) 0.0)
    ((:err_axisang_z __err_axisang_z) 0.0)
    ((:err_axisang_ang __err_axisang_ang) 0.0)
    ((:fb_rate_x __fb_rate_x) 0.0)
    ((:fb_rate_y __fb_rate_y) 0.0)
    ((:fb_rate_z __fb_rate_z) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _des_v_x (float __des_v_x))
   (setq _des_v_y (float __des_v_y))
   (setq _des_v_z (float __des_v_z))
   (setq _fb_a_x (float __fb_a_x))
   (setq _fb_a_y (float __fb_a_y))
   (setq _fb_a_z (float __fb_a_z))
   (setq _des_a_x (float __des_a_x))
   (setq _des_a_y (float __des_a_y))
   (setq _des_a_z (float __des_a_z))
   (setq _des_q_x (float __des_q_x))
   (setq _des_q_y (float __des_q_y))
   (setq _des_q_z (float __des_q_z))
   (setq _des_q_w (float __des_q_w))
   (setq _des_thr (float __des_thr))
   (setq _hover_percentage (float __hover_percentage))
   (setq _thr_scale_compensate (float __thr_scale_compensate))
   (setq _voltage (float __voltage))
   (setq _err_axisang_x (float __err_axisang_x))
   (setq _err_axisang_y (float __err_axisang_y))
   (setq _err_axisang_z (float __err_axisang_z))
   (setq _err_axisang_ang (float __err_axisang_ang))
   (setq _fb_rate_x (float __fb_rate_x))
   (setq _fb_rate_y (float __fb_rate_y))
   (setq _fb_rate_z (float __fb_rate_z))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:des_v_x
   (&optional __des_v_x)
   (if __des_v_x (setq _des_v_x __des_v_x)) _des_v_x)
  (:des_v_y
   (&optional __des_v_y)
   (if __des_v_y (setq _des_v_y __des_v_y)) _des_v_y)
  (:des_v_z
   (&optional __des_v_z)
   (if __des_v_z (setq _des_v_z __des_v_z)) _des_v_z)
  (:fb_a_x
   (&optional __fb_a_x)
   (if __fb_a_x (setq _fb_a_x __fb_a_x)) _fb_a_x)
  (:fb_a_y
   (&optional __fb_a_y)
   (if __fb_a_y (setq _fb_a_y __fb_a_y)) _fb_a_y)
  (:fb_a_z
   (&optional __fb_a_z)
   (if __fb_a_z (setq _fb_a_z __fb_a_z)) _fb_a_z)
  (:des_a_x
   (&optional __des_a_x)
   (if __des_a_x (setq _des_a_x __des_a_x)) _des_a_x)
  (:des_a_y
   (&optional __des_a_y)
   (if __des_a_y (setq _des_a_y __des_a_y)) _des_a_y)
  (:des_a_z
   (&optional __des_a_z)
   (if __des_a_z (setq _des_a_z __des_a_z)) _des_a_z)
  (:des_q_x
   (&optional __des_q_x)
   (if __des_q_x (setq _des_q_x __des_q_x)) _des_q_x)
  (:des_q_y
   (&optional __des_q_y)
   (if __des_q_y (setq _des_q_y __des_q_y)) _des_q_y)
  (:des_q_z
   (&optional __des_q_z)
   (if __des_q_z (setq _des_q_z __des_q_z)) _des_q_z)
  (:des_q_w
   (&optional __des_q_w)
   (if __des_q_w (setq _des_q_w __des_q_w)) _des_q_w)
  (:des_thr
   (&optional __des_thr)
   (if __des_thr (setq _des_thr __des_thr)) _des_thr)
  (:hover_percentage
   (&optional __hover_percentage)
   (if __hover_percentage (setq _hover_percentage __hover_percentage)) _hover_percentage)
  (:thr_scale_compensate
   (&optional __thr_scale_compensate)
   (if __thr_scale_compensate (setq _thr_scale_compensate __thr_scale_compensate)) _thr_scale_compensate)
  (:voltage
   (&optional __voltage)
   (if __voltage (setq _voltage __voltage)) _voltage)
  (:err_axisang_x
   (&optional __err_axisang_x)
   (if __err_axisang_x (setq _err_axisang_x __err_axisang_x)) _err_axisang_x)
  (:err_axisang_y
   (&optional __err_axisang_y)
   (if __err_axisang_y (setq _err_axisang_y __err_axisang_y)) _err_axisang_y)
  (:err_axisang_z
   (&optional __err_axisang_z)
   (if __err_axisang_z (setq _err_axisang_z __err_axisang_z)) _err_axisang_z)
  (:err_axisang_ang
   (&optional __err_axisang_ang)
   (if __err_axisang_ang (setq _err_axisang_ang __err_axisang_ang)) _err_axisang_ang)
  (:fb_rate_x
   (&optional __fb_rate_x)
   (if __fb_rate_x (setq _fb_rate_x __fb_rate_x)) _fb_rate_x)
  (:fb_rate_y
   (&optional __fb_rate_y)
   (if __fb_rate_y (setq _fb_rate_y __fb_rate_y)) _fb_rate_y)
  (:fb_rate_z
   (&optional __fb_rate_z)
   (if __fb_rate_z (setq _fb_rate_z __fb_rate_z)) _fb_rate_z)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _des_v_x
    8
    ;; float64 _des_v_y
    8
    ;; float64 _des_v_z
    8
    ;; float64 _fb_a_x
    8
    ;; float64 _fb_a_y
    8
    ;; float64 _fb_a_z
    8
    ;; float64 _des_a_x
    8
    ;; float64 _des_a_y
    8
    ;; float64 _des_a_z
    8
    ;; float64 _des_q_x
    8
    ;; float64 _des_q_y
    8
    ;; float64 _des_q_z
    8
    ;; float64 _des_q_w
    8
    ;; float64 _des_thr
    8
    ;; float64 _hover_percentage
    8
    ;; float64 _thr_scale_compensate
    8
    ;; float64 _voltage
    8
    ;; float64 _err_axisang_x
    8
    ;; float64 _err_axisang_y
    8
    ;; float64 _err_axisang_z
    8
    ;; float64 _err_axisang_ang
    8
    ;; float64 _fb_rate_x
    8
    ;; float64 _fb_rate_y
    8
    ;; float64 _fb_rate_z
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _des_v_x
       (sys::poke _des_v_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _des_v_y
       (sys::poke _des_v_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _des_v_z
       (sys::poke _des_v_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fb_a_x
       (sys::poke _fb_a_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fb_a_y
       (sys::poke _fb_a_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fb_a_z
       (sys::poke _fb_a_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _des_a_x
       (sys::poke _des_a_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _des_a_y
       (sys::poke _des_a_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _des_a_z
       (sys::poke _des_a_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _des_q_x
       (sys::poke _des_q_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _des_q_y
       (sys::poke _des_q_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _des_q_z
       (sys::poke _des_q_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _des_q_w
       (sys::poke _des_q_w (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _des_thr
       (sys::poke _des_thr (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _hover_percentage
       (sys::poke _hover_percentage (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _thr_scale_compensate
       (sys::poke _thr_scale_compensate (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _voltage
       (sys::poke _voltage (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _err_axisang_x
       (sys::poke _err_axisang_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _err_axisang_y
       (sys::poke _err_axisang_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _err_axisang_z
       (sys::poke _err_axisang_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _err_axisang_ang
       (sys::poke _err_axisang_ang (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fb_rate_x
       (sys::poke _fb_rate_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fb_rate_y
       (sys::poke _fb_rate_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fb_rate_z
       (sys::poke _fb_rate_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _des_v_x
     (setq _des_v_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _des_v_y
     (setq _des_v_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _des_v_z
     (setq _des_v_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fb_a_x
     (setq _fb_a_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fb_a_y
     (setq _fb_a_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fb_a_z
     (setq _fb_a_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _des_a_x
     (setq _des_a_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _des_a_y
     (setq _des_a_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _des_a_z
     (setq _des_a_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _des_q_x
     (setq _des_q_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _des_q_y
     (setq _des_q_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _des_q_z
     (setq _des_q_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _des_q_w
     (setq _des_q_w (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _des_thr
     (setq _des_thr (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _hover_percentage
     (setq _hover_percentage (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _thr_scale_compensate
     (setq _thr_scale_compensate (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _voltage
     (setq _voltage (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _err_axisang_x
     (setq _err_axisang_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _err_axisang_y
     (setq _err_axisang_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _err_axisang_z
     (setq _err_axisang_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _err_axisang_ang
     (setq _err_axisang_ang (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fb_rate_x
     (setq _fb_rate_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fb_rate_y
     (setq _fb_rate_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fb_rate_z
     (setq _fb_rate_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get quadrotor_msgs::Px4ctrlDebug :md5sum-) "8adafd9362e5a8fc6c85e6f460fbfc53")
(setf (get quadrotor_msgs::Px4ctrlDebug :datatype-) "quadrotor_msgs/Px4ctrlDebug")
(setf (get quadrotor_msgs::Px4ctrlDebug :definition-)
      "Header header

float64 des_v_x
float64 des_v_y
float64 des_v_z

float64 fb_a_x
float64 fb_a_y
float64 fb_a_z

float64 des_a_x
float64 des_a_y
float64 des_a_z

float64 des_q_x
float64 des_q_y
float64 des_q_z
float64 des_q_w

float64 des_thr
float64 hover_percentage
float64 thr_scale_compensate
float64 voltage

float64 err_axisang_x
float64 err_axisang_y
float64 err_axisang_z
float64 err_axisang_ang

float64 fb_rate_x
float64 fb_rate_y
float64 fb_rate_z


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

")



(provide :quadrotor_msgs/Px4ctrlDebug "8adafd9362e5a8fc6c85e6f460fbfc53")


