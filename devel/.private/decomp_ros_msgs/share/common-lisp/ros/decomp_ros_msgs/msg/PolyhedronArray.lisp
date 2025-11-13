; Auto-generated. Do not edit!


(cl:in-package decomp_ros_msgs-msg)


;//! \htmlinclude PolyhedronArray.msg.html

(cl:defclass <PolyhedronArray> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (polyhedrons
    :reader polyhedrons
    :initarg :polyhedrons
    :type (cl:vector decomp_ros_msgs-msg:Polyhedron)
   :initform (cl:make-array 0 :element-type 'decomp_ros_msgs-msg:Polyhedron :initial-element (cl:make-instance 'decomp_ros_msgs-msg:Polyhedron))))
)

(cl:defclass PolyhedronArray (<PolyhedronArray>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PolyhedronArray>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PolyhedronArray)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name decomp_ros_msgs-msg:<PolyhedronArray> is deprecated: use decomp_ros_msgs-msg:PolyhedronArray instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <PolyhedronArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader decomp_ros_msgs-msg:header-val is deprecated.  Use decomp_ros_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'polyhedrons-val :lambda-list '(m))
(cl:defmethod polyhedrons-val ((m <PolyhedronArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader decomp_ros_msgs-msg:polyhedrons-val is deprecated.  Use decomp_ros_msgs-msg:polyhedrons instead.")
  (polyhedrons m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PolyhedronArray>) ostream)
  "Serializes a message object of type '<PolyhedronArray>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'polyhedrons))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'polyhedrons))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PolyhedronArray>) istream)
  "Deserializes a message object of type '<PolyhedronArray>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'polyhedrons) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'polyhedrons)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'decomp_ros_msgs-msg:Polyhedron))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PolyhedronArray>)))
  "Returns string type for a message object of type '<PolyhedronArray>"
  "decomp_ros_msgs/PolyhedronArray")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PolyhedronArray)))
  "Returns string type for a message object of type 'PolyhedronArray"
  "decomp_ros_msgs/PolyhedronArray")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PolyhedronArray>)))
  "Returns md5sum for a message object of type '<PolyhedronArray>"
  "ff07031dce96f472bf57a9bfa0a84d0a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PolyhedronArray)))
  "Returns md5sum for a message object of type 'PolyhedronArray"
  "ff07031dce96f472bf57a9bfa0a84d0a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PolyhedronArray>)))
  "Returns full string definition for message of type '<PolyhedronArray>"
  (cl:format cl:nil "Header header~%Polyhedron[] polyhedrons~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: decomp_ros_msgs/Polyhedron~%geometry_msgs/Point[] points~%geometry_msgs/Point[] normals #norm is an outer vector~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PolyhedronArray)))
  "Returns full string definition for message of type 'PolyhedronArray"
  (cl:format cl:nil "Header header~%Polyhedron[] polyhedrons~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: decomp_ros_msgs/Polyhedron~%geometry_msgs/Point[] points~%geometry_msgs/Point[] normals #norm is an outer vector~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PolyhedronArray>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'polyhedrons) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PolyhedronArray>))
  "Converts a ROS message object to a list"
  (cl:list 'PolyhedronArray
    (cl:cons ':header (header msg))
    (cl:cons ':polyhedrons (polyhedrons msg))
))
