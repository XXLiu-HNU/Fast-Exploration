; Auto-generated. Do not edit!


(cl:in-package quadrotor_msgs-msg)


;//! \htmlinclude GoalSet.msg.html

(cl:defclass <GoalSet> (roslisp-msg-protocol:ros-message)
  ((drone_id
    :reader drone_id
    :initarg :drone_id
    :type cl:fixnum
    :initform 0)
   (goal
    :reader goal
    :initarg :goal
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass GoalSet (<GoalSet>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GoalSet>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GoalSet)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name quadrotor_msgs-msg:<GoalSet> is deprecated: use quadrotor_msgs-msg:GoalSet instead.")))

(cl:ensure-generic-function 'drone_id-val :lambda-list '(m))
(cl:defmethod drone_id-val ((m <GoalSet>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader quadrotor_msgs-msg:drone_id-val is deprecated.  Use quadrotor_msgs-msg:drone_id instead.")
  (drone_id m))

(cl:ensure-generic-function 'goal-val :lambda-list '(m))
(cl:defmethod goal-val ((m <GoalSet>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader quadrotor_msgs-msg:goal-val is deprecated.  Use quadrotor_msgs-msg:goal instead.")
  (goal m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GoalSet>) ostream)
  "Serializes a message object of type '<GoalSet>"
  (cl:let* ((signed (cl:slot-value msg 'drone_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'goal))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GoalSet>) istream)
  "Deserializes a message object of type '<GoalSet>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'drone_id) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  (cl:setf (cl:slot-value msg 'goal) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'goal)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GoalSet>)))
  "Returns string type for a message object of type '<GoalSet>"
  "quadrotor_msgs/GoalSet")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GoalSet)))
  "Returns string type for a message object of type 'GoalSet"
  "quadrotor_msgs/GoalSet")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GoalSet>)))
  "Returns md5sum for a message object of type '<GoalSet>"
  "647346ea582a0f372d5aad4ae220f0b2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GoalSet)))
  "Returns md5sum for a message object of type 'GoalSet"
  "647346ea582a0f372d5aad4ae220f0b2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GoalSet>)))
  "Returns full string definition for message of type '<GoalSet>"
  (cl:format cl:nil "int16 drone_id~%float32[3] goal~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GoalSet)))
  "Returns full string definition for message of type 'GoalSet"
  (cl:format cl:nil "int16 drone_id~%float32[3] goal~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GoalSet>))
  (cl:+ 0
     2
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'goal) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GoalSet>))
  "Converts a ROS message object to a list"
  (cl:list 'GoalSet
    (cl:cons ':drone_id (drone_id msg))
    (cl:cons ':goal (goal msg))
))
