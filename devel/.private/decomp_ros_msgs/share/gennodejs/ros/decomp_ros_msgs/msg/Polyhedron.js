// Auto-generated. Do not edit!

// (in-package decomp_ros_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class Polyhedron {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.points = null;
      this.normals = null;
    }
    else {
      if (initObj.hasOwnProperty('points')) {
        this.points = initObj.points
      }
      else {
        this.points = [];
      }
      if (initObj.hasOwnProperty('normals')) {
        this.normals = initObj.normals
      }
      else {
        this.normals = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Polyhedron
    // Serialize message field [points]
    // Serialize the length for message field [points]
    bufferOffset = _serializer.uint32(obj.points.length, buffer, bufferOffset);
    obj.points.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [normals]
    // Serialize the length for message field [normals]
    bufferOffset = _serializer.uint32(obj.normals.length, buffer, bufferOffset);
    obj.normals.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Polyhedron
    let len;
    let data = new Polyhedron(null);
    // Deserialize message field [points]
    // Deserialize array length for message field [points]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.points = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.points[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [normals]
    // Deserialize array length for message field [normals]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.normals = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.normals[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 24 * object.points.length;
    length += 24 * object.normals.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'decomp_ros_msgs/Polyhedron';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '30e67f500a403ad4875ae4600d46dde5';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new Polyhedron(null);
    if (msg.points !== undefined) {
      resolved.points = new Array(msg.points.length);
      for (let i = 0; i < resolved.points.length; ++i) {
        resolved.points[i] = geometry_msgs.msg.Point.Resolve(msg.points[i]);
      }
    }
    else {
      resolved.points = []
    }

    if (msg.normals !== undefined) {
      resolved.normals = new Array(msg.normals.length);
      for (let i = 0; i < resolved.normals.length; ++i) {
        resolved.normals[i] = geometry_msgs.msg.Point.Resolve(msg.normals[i]);
      }
    }
    else {
      resolved.normals = []
    }

    return resolved;
    }
};

module.exports = Polyhedron;
