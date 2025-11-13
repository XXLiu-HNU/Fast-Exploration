// Auto-generated. Do not edit!

// (in-package decomp_ros_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Ellipsoid {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.d = null;
      this.E = null;
    }
    else {
      if (initObj.hasOwnProperty('d')) {
        this.d = initObj.d
      }
      else {
        this.d = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('E')) {
        this.E = initObj.E
      }
      else {
        this.E = new Array(9).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Ellipsoid
    // Check that the constant length array field [d] has the right length
    if (obj.d.length !== 3) {
      throw new Error('Unable to serialize array field d - length must be 3')
    }
    // Serialize message field [d]
    bufferOffset = _arraySerializer.float64(obj.d, buffer, bufferOffset, 3);
    // Check that the constant length array field [E] has the right length
    if (obj.E.length !== 9) {
      throw new Error('Unable to serialize array field E - length must be 9')
    }
    // Serialize message field [E]
    bufferOffset = _arraySerializer.float64(obj.E, buffer, bufferOffset, 9);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Ellipsoid
    let len;
    let data = new Ellipsoid(null);
    // Deserialize message field [d]
    data.d = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [E]
    data.E = _arrayDeserializer.float64(buffer, bufferOffset, 9)
    return data;
  }

  static getMessageSize(object) {
    return 96;
  }

  static datatype() {
    // Returns string type for a message object
    return 'decomp_ros_msgs/Ellipsoid';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '56675b593d9a5da51b91765fa8f29c87';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[3] d
    float64[9] E
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Ellipsoid(null);
    if (msg.d !== undefined) {
      resolved.d = msg.d;
    }
    else {
      resolved.d = new Array(3).fill(0)
    }

    if (msg.E !== undefined) {
      resolved.E = msg.E;
    }
    else {
      resolved.E = new Array(9).fill(0)
    }

    return resolved;
    }
};

module.exports = Ellipsoid;
