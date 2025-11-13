; Auto-generated. Do not edit!


(cl:in-package quadrotor_msgs-msg)


;//! \htmlinclude TakeoffLand.msg.html

(cl:defclass <TakeoffLand> (roslisp-msg-protocol:ros-message)
  ((takeoff_land_cmd
    :reader takeoff_land_cmd
    :initarg :takeoff_land_cmd
    :type cl:fixnum
    :initform 0))
)

(cl:defclass TakeoffLand (<TakeoffLand>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TakeoffLand>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TakeoffLand)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name quadrotor_msgs-msg:<TakeoffLand> is deprecated: use quadrotor_msgs-msg:TakeoffLand instead.")))

(cl:ensure-generic-function 'takeoff_land_cmd-val :lambda-list '(m))
(cl:defmethod takeoff_land_cmd-val ((m <TakeoffLand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader quadrotor_msgs-msg:takeoff_land_cmd-val is deprecated.  Use quadrotor_msgs-msg:takeoff_land_cmd instead.")
  (takeoff_land_cmd m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<TakeoffLand>)))
    "Constants for message type '<TakeoffLand>"
  '((:TAKEOFF . 1)
    (:LAND . 2))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'TakeoffLand)))
    "Constants for message type 'TakeoffLand"
  '((:TAKEOFF . 1)
    (:LAND . 2))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TakeoffLand>) ostream)
  "Serializes a message object of type '<TakeoffLand>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'takeoff_land_cmd)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TakeoffLand>) istream)
  "Deserializes a message object of type '<TakeoffLand>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'takeoff_land_cmd)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TakeoffLand>)))
  "Returns string type for a message object of type '<TakeoffLand>"
  "quadrotor_msgs/TakeoffLand")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TakeoffLand)))
  "Returns string type for a message object of type 'TakeoffLand"
  "quadrotor_msgs/TakeoffLand")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TakeoffLand>)))
  "Returns md5sum for a message object of type '<TakeoffLand>"
  "b30b3b93263aae01746755d3b8ff620f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TakeoffLand)))
  "Returns md5sum for a message object of type 'TakeoffLand"
  "b30b3b93263aae01746755d3b8ff620f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TakeoffLand>)))
  "Returns full string definition for message of type '<TakeoffLand>"
  (cl:format cl:nil "uint8 TAKEOFF = 1~%uint8 LAND = 2~%uint8 takeoff_land_cmd~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TakeoffLand)))
  "Returns full string definition for message of type 'TakeoffLand"
  (cl:format cl:nil "uint8 TAKEOFF = 1~%uint8 LAND = 2~%uint8 takeoff_land_cmd~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TakeoffLand>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TakeoffLand>))
  "Converts a ROS message object to a list"
  (cl:list 'TakeoffLand
    (cl:cons ':takeoff_land_cmd (takeoff_land_cmd msg))
))
