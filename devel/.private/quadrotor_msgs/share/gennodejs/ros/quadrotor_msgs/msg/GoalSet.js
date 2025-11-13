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

class GoalSet {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.drone_id = null;
      this.goal = null;
    }
    else {
      if (initObj.hasOwnProperty('drone_id')) {
        this.drone_id = initObj.drone_id
      }
      else {
        this.drone_id = 0;
      }
      if (initObj.hasOwnProperty('goal')) {
        this.goal = initObj.goal
      }
      else {
        this.goal = new Array(3).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GoalSet
    // Serialize message field [drone_id]
    bufferOffset = _serializer.int16(obj.drone_id, buffer, bufferOffset);
    // Check that the constant length array field [goal] has the right length
    if (obj.goal.length !== 3) {
      throw new Error('Unable to serialize array field goal - length must be 3')
    }
    // Serialize message field [goal]
    bufferOffset = _arraySerializer.float32(obj.goal, buffer, bufferOffset, 3);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GoalSet
    let len;
    let data = new GoalSet(null);
    // Deserialize message field [drone_id]
    data.drone_id = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [goal]
    data.goal = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    return data;
  }

  static getMessageSize(object) {
    return 14;
  }

  static datatype() {
    // Returns string type for a message object
    return 'quadrotor_msgs/GoalSet';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '647346ea582a0f372d5aad4ae220f0b2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16 drone_id
    float32[3] goal
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GoalSet(null);
    if (msg.drone_id !== undefined) {
      resolved.drone_id = msg.drone_id;
    }
    else {
      resolved.drone_id = 0
    }

    if (msg.goal !== undefined) {
      resolved.goal = msg.goal;
    }
    else {
      resolved.goal = new Array(3).fill(0)
    }

    return resolved;
    }
};

module.exports = GoalSet;
