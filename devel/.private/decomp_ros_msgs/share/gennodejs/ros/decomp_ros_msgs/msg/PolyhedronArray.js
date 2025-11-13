// Auto-generated. Do not edit!

// (in-package decomp_ros_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Polyhedron = require('./Polyhedron.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class PolyhedronArray {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.polyhedrons = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('polyhedrons')) {
        this.polyhedrons = initObj.polyhedrons
      }
      else {
        this.polyhedrons = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PolyhedronArray
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [polyhedrons]
    // Serialize the length for message field [polyhedrons]
    bufferOffset = _serializer.uint32(obj.polyhedrons.length, buffer, bufferOffset);
    obj.polyhedrons.forEach((val) => {
      bufferOffset = Polyhedron.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PolyhedronArray
    let len;
    let data = new PolyhedronArray(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [polyhedrons]
    // Deserialize array length for message field [polyhedrons]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.polyhedrons = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.polyhedrons[i] = Polyhedron.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.polyhedrons.forEach((val) => {
      length += Polyhedron.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'decomp_ros_msgs/PolyhedronArray';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ff07031dce96f472bf57a9bfa0a84d0a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    Polyhedron[] polyhedrons
    
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
    MSG: decomp_ros_msgs/Polyhedron
    geometry_msgs/Point[] points
    geometry_msgs/Point[] normals #norm is an outer vector
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PolyhedronArray(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.polyhedrons !== undefined) {
      resolved.polyhedrons = new Array(msg.polyhedrons.length);
      for (let i = 0; i < resolved.polyhedrons.length; ++i) {
        resolved.polyhedrons[i] = Polyhedron.Resolve(msg.polyhedrons[i]);
      }
    }
    else {
      resolved.polyhedrons = []
    }

    return resolved;
    }
};

module.exports = PolyhedronArray;
