; Auto-generated. Do not edit!


(cl:in-package decomp_ros_msgs-msg)


;//! \htmlinclude EllipsoidArray.msg.html

(cl:defclass <EllipsoidArray> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (ellipsoids
    :reader ellipsoids
    :initarg :ellipsoids
    :type (cl:vector decomp_ros_msgs-msg:Ellipsoid)
   :initform (cl:make-array 0 :element-type 'decomp_ros_msgs-msg:Ellipsoid :initial-element (cl:make-instance 'decomp_ros_msgs-msg:Ellipsoid))))
)

(cl:defclass EllipsoidArray (<EllipsoidArray>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <EllipsoidArray>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'EllipsoidArray)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name decomp_ros_msgs-msg:<EllipsoidArray> is deprecated: use decomp_ros_msgs-msg:EllipsoidArray instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <EllipsoidArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader decomp_ros_msgs-msg:header-val is deprecated.  Use decomp_ros_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'ellipsoids-val :lambda-list '(m))
(cl:defmethod ellipsoids-val ((m <EllipsoidArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader decomp_ros_msgs-msg:ellipsoids-val is deprecated.  Use decomp_ros_msgs-msg:ellipsoids instead.")
  (ellipsoids m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <EllipsoidArray>) ostream)
  "Serializes a message object of type '<EllipsoidArray>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'ellipsoids))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'ellipsoids))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <EllipsoidArray>) istream)
  "Deserializes a message object of type '<EllipsoidArray>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'ellipsoids) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'ellipsoids)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'decomp_ros_msgs-msg:Ellipsoid))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<EllipsoidArray>)))
  "Returns string type for a message object of type '<EllipsoidArray>"
  "decomp_ros_msgs/EllipsoidArray")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'EllipsoidArray)))
  "Returns string type for a message object of type 'EllipsoidArray"
  "decomp_ros_msgs/EllipsoidArray")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<EllipsoidArray>)))
  "Returns md5sum for a message object of type '<EllipsoidArray>"
  "e2c31e58d2b4b09679be4a3c12fffb19")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'EllipsoidArray)))
  "Returns md5sum for a message object of type 'EllipsoidArray"
  "e2c31e58d2b4b09679be4a3c12fffb19")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<EllipsoidArray>)))
  "Returns full string definition for message of type '<EllipsoidArray>"
  (cl:format cl:nil "Header header~%Ellipsoid[] ellipsoids~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: decomp_ros_msgs/Ellipsoid~%float64[3] d~%float64[9] E~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'EllipsoidArray)))
  "Returns full string definition for message of type 'EllipsoidArray"
  (cl:format cl:nil "Header header~%Ellipsoid[] ellipsoids~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: decomp_ros_msgs/Ellipsoid~%float64[3] d~%float64[9] E~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <EllipsoidArray>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'ellipsoids) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <EllipsoidArray>))
  "Converts a ROS message object to a list"
  (cl:list 'EllipsoidArray
    (cl:cons ':header (header msg))
    (cl:cons ':ellipsoids (ellipsoids msg))
))
