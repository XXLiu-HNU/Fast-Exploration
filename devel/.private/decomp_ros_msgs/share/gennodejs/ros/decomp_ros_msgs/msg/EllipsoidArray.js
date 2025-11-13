// Auto-generated. Do not edit!

// (in-package decomp_ros_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Ellipsoid = require('./Ellipsoid.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class EllipsoidArray {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.ellipsoids = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('ellipsoids')) {
        this.ellipsoids = initObj.ellipsoids
      }
      else {
        this.ellipsoids = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type EllipsoidArray
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [ellipsoids]
    // Serialize the length for message field [ellipsoids]
    bufferOffset = _serializer.uint32(obj.ellipsoids.length, buffer, bufferOffset);
    obj.ellipsoids.forEach((val) => {
      bufferOffset = Ellipsoid.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type EllipsoidArray
    let len;
    let data = new EllipsoidArray(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [ellipsoids]
    // Deserialize array length for message field [ellipsoids]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.ellipsoids = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.ellipsoids[i] = Ellipsoid.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 96 * object.ellipsoids.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'decomp_ros_msgs/EllipsoidArray';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e2c31e58d2b4b09679be4a3c12fffb19';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    Ellipsoid[] ellipsoids
    
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
    
    ================================================================================
    MSG: decomp_ros_msgs/Ellipsoid
    float64[3] d
    float64[9] E
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new EllipsoidArray(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.ellipsoids !== undefined) {
      resolved.ellipsoids = new Array(msg.ellipsoids.length);
      for (let i = 0; i < resolved.ellipsoids.length; ++i) {
        resolved.ellipsoids[i] = Ellipsoid.Resolve(msg.ellipsoids[i]);
      }
    }
    else {
      resolved.ellipsoids = []
    }

    return resolved;
    }
};

module.exports = EllipsoidArray;
