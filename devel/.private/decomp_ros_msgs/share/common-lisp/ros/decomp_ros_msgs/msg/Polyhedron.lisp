; Auto-generated. Do not edit!


(cl:in-package decomp_ros_msgs-msg)


;//! \htmlinclude Polyhedron.msg.html

(cl:defclass <Polyhedron> (roslisp-msg-protocol:ros-message)
  ((points
    :reader points
    :initarg :points
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point)))
   (normals
    :reader normals
    :initarg :normals
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point))))
)

(cl:defclass Polyhedron (<Polyhedron>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Polyhedron>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Polyhedron)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name decomp_ros_msgs-msg:<Polyhedron> is deprecated: use decomp_ros_msgs-msg:Polyhedron instead.")))

(cl:ensure-generic-function 'points-val :lambda-list '(m))
(cl:defmethod points-val ((m <Polyhedron>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader decomp_ros_msgs-msg:points-val is deprecated.  Use decomp_ros_msgs-msg:points instead.")
  (points m))

(cl:ensure-generic-function 'normals-val :lambda-list '(m))
(cl:defmethod normals-val ((m <Polyhedron>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader decomp_ros_msgs-msg:normals-val is deprecated.  Use decomp_ros_msgs-msg:normals instead.")
  (normals m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Polyhedron>) ostream)
  "Serializes a message object of type '<Polyhedron>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'points))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'points))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'normals))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'normals))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Polyhedron>) istream)
  "Deserializes a message object of type '<Polyhedron>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'points) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'points)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'normals) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'normals)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Polyhedron>)))
  "Returns string type for a message object of type '<Polyhedron>"
  "decomp_ros_msgs/Polyhedron")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Polyhedron)))
  "Returns string type for a message object of type 'Polyhedron"
  "decomp_ros_msgs/Polyhedron")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Polyhedron>)))
  "Returns md5sum for a message object of type '<Polyhedron>"
  "30e67f500a403ad4875ae4600d46dde5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Polyhedron)))
  "Returns md5sum for a message object of type 'Polyhedron"
  "30e67f500a403ad4875ae4600d46dde5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Polyhedron>)))
  "Returns full string definition for message of type '<Polyhedron>"
  (cl:format cl:nil "geometry_msgs/Point[] points~%geometry_msgs/Point[] normals #norm is an outer vector~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Polyhedron)))
  "Returns full string definition for message of type 'Polyhedron"
  (cl:format cl:nil "geometry_msgs/Point[] points~%geometry_msgs/Point[] normals #norm is an outer vector~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Polyhedron>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'points) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'normals) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Polyhedron>))
  "Converts a ROS message object to a list"
  (cl:list 'Polyhedron
    (cl:cons ':points (points msg))
    (cl:cons ':normals (normals msg))
))
