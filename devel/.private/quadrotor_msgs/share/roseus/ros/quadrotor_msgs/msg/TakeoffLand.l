;; Auto-generated. Do not edit!


(when (boundp 'quadrotor_msgs::TakeoffLand)
  (if (not (find-package "QUADROTOR_MSGS"))
    (make-package "QUADROTOR_MSGS"))
  (shadow 'TakeoffLand (find-package "QUADROTOR_MSGS")))
(unless (find-package "QUADROTOR_MSGS::TAKEOFFLAND")
  (make-package "QUADROTOR_MSGS::TAKEOFFLAND"))

(in-package "ROS")
;;//! \htmlinclude TakeoffLand.msg.html


(intern "*TAKEOFF*" (find-package "QUADROTOR_MSGS::TAKEOFFLAND"))
(shadow '*TAKEOFF* (find-package "QUADROTOR_MSGS::TAKEOFFLAND"))
(defconstant quadrotor_msgs::TakeoffLand::*TAKEOFF* 1)
(intern "*LAND*" (find-package "QUADROTOR_MSGS::TAKEOFFLAND"))
(shadow '*LAND* (find-package "QUADROTOR_MSGS::TAKEOFFLAND"))
(defconstant quadrotor_msgs::TakeoffLand::*LAND* 2)

(defun quadrotor_msgs::TakeoffLand-to-symbol (const)
  (cond
        ((= const 1) 'quadrotor_msgs::TakeoffLand::*TAKEOFF*)
        ((= const 2) 'quadrotor_msgs::TakeoffLand::*LAND*)
        (t nil)))

(defclass quadrotor_msgs::TakeoffLand
  :super ros::object
  :slots (_takeoff_land_cmd ))

(defmethod quadrotor_msgs::TakeoffLand
  (:init
   (&key
    ((:takeoff_land_cmd __takeoff_land_cmd) 0)
    )
   (send-super :init)
   (setq _takeoff_land_cmd (round __takeoff_land_cmd))
   self)
  (:takeoff_land_cmd
   (&optional __takeoff_land_cmd)
   (if __takeoff_land_cmd (setq _takeoff_land_cmd __takeoff_land_cmd)) _takeoff_land_cmd)
  (:serialization-length
   ()
   (+
    ;; uint8 _takeoff_land_cmd
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _takeoff_land_cmd
       (write-byte _takeoff_land_cmd s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _takeoff_land_cmd
     (setq _takeoff_land_cmd (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get quadrotor_msgs::TakeoffLand :md5sum-) "b30b3b93263aae01746755d3b8ff620f")
(setf (get quadrotor_msgs::TakeoffLand :datatype-) "quadrotor_msgs/TakeoffLand")
(setf (get quadrotor_msgs::TakeoffLand :definition-)
      "uint8 TAKEOFF = 1
uint8 LAND = 2
uint8 takeoff_land_cmd
")



(provide :quadrotor_msgs/TakeoffLand "b30b3b93263aae01746755d3b8ff620f")


