; Auto-generated. Do not edit!


(cl:in-package decomp_ros_msgs-msg)


;//! \htmlinclude Ellipsoid.msg.html

(cl:defclass <Ellipsoid> (roslisp-msg-protocol:ros-message)
  ((d
    :reader d
    :initarg :d
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (E
    :reader E
    :initarg :E
    :type (cl:vector cl:float)
   :initform (cl:make-array 9 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass Ellipsoid (<Ellipsoid>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Ellipsoid>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Ellipsoid)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name decomp_ros_msgs-msg:<Ellipsoid> is deprecated: use decomp_ros_msgs-msg:Ellipsoid instead.")))

(cl:ensure-generic-function 'd-val :lambda-list '(m))
(cl:defmethod d-val ((m <Ellipsoid>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader decomp_ros_msgs-msg:d-val is deprecated.  Use decomp_ros_msgs-msg:d instead.")
  (d m))

(cl:ensure-generic-function 'E-val :lambda-list '(m))
(cl:defmethod E-val ((m <Ellipsoid>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader decomp_ros_msgs-msg:E-val is deprecated.  Use decomp_ros_msgs-msg:E instead.")
  (E m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Ellipsoid>) ostream)
  "Serializes a message object of type '<Ellipsoid>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'd))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'E))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Ellipsoid>) istream)
  "Deserializes a message object of type '<Ellipsoid>"
  (cl:setf (cl:slot-value msg 'd) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'd)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'E) (cl:make-array 9))
  (cl:let ((vals (cl:slot-value msg 'E)))
    (cl:dotimes (i 9)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Ellipsoid>)))
  "Returns string type for a message object of type '<Ellipsoid>"
  "decomp_ros_msgs/Ellipsoid")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Ellipsoid)))
  "Returns string type for a message object of type 'Ellipsoid"
  "decomp_ros_msgs/Ellipsoid")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Ellipsoid>)))
  "Returns md5sum for a message object of type '<Ellipsoid>"
  "56675b593d9a5da51b91765fa8f29c87")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Ellipsoid)))
  "Returns md5sum for a message object of type 'Ellipsoid"
  "56675b593d9a5da51b91765fa8f29c87")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Ellipsoid>)))
  "Returns full string definition for message of type '<Ellipsoid>"
  (cl:format cl:nil "float64[3] d~%float64[9] E~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Ellipsoid)))
  "Returns full string definition for message of type 'Ellipsoid"
  (cl:format cl:nil "float64[3] d~%float64[9] E~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Ellipsoid>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'd) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'E) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Ellipsoid>))
  "Converts a ROS message object to a list"
  (cl:list 'Ellipsoid
    (cl:cons ':d (d msg))
    (cl:cons ':E (E msg))
))
