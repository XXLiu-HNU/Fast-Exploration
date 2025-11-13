// Auto-generated. Do not edit!

// (in-package quadrotor_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class TakeoffLand {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.takeoff_land_cmd = null;
    }
    else {
      if (initObj.hasOwnProperty('takeoff_land_cmd')) {
        this.takeoff_land_cmd = initObj.takeoff_land_cmd
      }
      else {
        this.takeoff_land_cmd = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type TakeoffLand
    // Serialize message field [takeoff_land_cmd]
    bufferOffset = _serializer.uint8(obj.takeoff_land_cmd, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type TakeoffLand
    let len;
    let data = new TakeoffLand(null);
    // Deserialize message field [takeoff_land_cmd]
    data.takeoff_land_cmd = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'quadrotor_msgs/TakeoffLand';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b30b3b93263aae01746755d3b8ff620f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 TAKEOFF = 1
    uint8 LAND = 2
    uint8 takeoff_land_cmd
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new TakeoffLand(null);
    if (msg.takeoff_land_cmd !== undefined) {
      resolved.takeoff_land_cmd = msg.takeoff_land_cmd;
    }
    else {
      resolved.takeoff_land_cmd = 0
    }

    return resolved;
    }
};

// Constants for message
TakeoffLand.Constants = {
  TAKEOFF: 1,
  LAND: 2,
}

module.exports = TakeoffLand;
