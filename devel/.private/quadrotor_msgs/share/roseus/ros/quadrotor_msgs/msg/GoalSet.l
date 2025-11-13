;; Auto-generated. Do not edit!


(when (boundp 'quadrotor_msgs::GoalSet)
  (if (not (find-package "QUADROTOR_MSGS"))
    (make-package "QUADROTOR_MSGS"))
  (shadow 'GoalSet (find-package "QUADROTOR_MSGS")))
(unless (find-package "QUADROTOR_MSGS::GOALSET")
  (make-package "QUADROTOR_MSGS::GOALSET"))

(in-package "ROS")
;;//! \htmlinclude GoalSet.msg.html


(defclass quadrotor_msgs::GoalSet
  :super ros::object
  :slots (_drone_id _goal ))

(defmethod quadrotor_msgs::GoalSet
  (:init
   (&key
    ((:drone_id __drone_id) 0)
    ((:goal __goal) (make-array 3 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _drone_id (round __drone_id))
   (setq _goal __goal)
   self)
  (:drone_id
   (&optional __drone_id)
   (if __drone_id (setq _drone_id __drone_id)) _drone_id)
  (:goal
   (&optional __goal)
   (if __goal (setq _goal __goal)) _goal)
  (:serialization-length
   ()
   (+
    ;; int16 _drone_id
    2
    ;; float32[3] _goal
    (* 4    3)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16 _drone_id
       (write-word _drone_id s)
     ;; float32[3] _goal
     (dotimes (i 3)
       (sys::poke (elt _goal i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _drone_id
     (setq _drone_id (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; float32[3] _goal
   (dotimes (i (length _goal))
     (setf (elt _goal i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;;
   self)
  )

(setf (get quadrotor_msgs::GoalSet :md5sum-) "647346ea582a0f372d5aad4ae220f0b2")
(setf (get quadrotor_msgs::GoalSet :datatype-) "quadrotor_msgs/GoalSet")
(setf (get quadrotor_msgs::GoalSet :definition-)
      "int16 drone_id
float32[3] goal

")



(provide :quadrotor_msgs/GoalSet "647346ea582a0f372d5aad4ae220f0b2")


