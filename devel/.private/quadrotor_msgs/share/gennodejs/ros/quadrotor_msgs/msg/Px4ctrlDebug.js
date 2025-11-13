// Auto-generated. Do not edit!

// (in-package quadrotor_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class Px4ctrlDebug {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.des_v_x = null;
      this.des_v_y = null;
      this.des_v_z = null;
      this.fb_a_x = null;
      this.fb_a_y = null;
      this.fb_a_z = null;
      this.des_a_x = null;
      this.des_a_y = null;
      this.des_a_z = null;
      this.des_q_x = null;
      this.des_q_y = null;
      this.des_q_z = null;
      this.des_q_w = null;
      this.des_thr = null;
      this.hover_percentage = null;
      this.thr_scale_compensate = null;
      this.voltage = null;
      this.err_axisang_x = null;
      this.err_axisang_y = null;
      this.err_axisang_z = null;
      this.err_axisang_ang = null;
      this.fb_rate_x = null;
      this.fb_rate_y = null;
      this.fb_rate_z = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('des_v_x')) {
        this.des_v_x = initObj.des_v_x
      }
      else {
        this.des_v_x = 0.0;
      }
      if (initObj.hasOwnProperty('des_v_y')) {
        this.des_v_y = initObj.des_v_y
      }
      else {
        this.des_v_y = 0.0;
      }
      if (initObj.hasOwnProperty('des_v_z')) {
        this.des_v_z = initObj.des_v_z
      }
      else {
        this.des_v_z = 0.0;
      }
      if (initObj.hasOwnProperty('fb_a_x')) {
        this.fb_a_x = initObj.fb_a_x
      }
      else {
        this.fb_a_x = 0.0;
      }
      if (initObj.hasOwnProperty('fb_a_y')) {
        this.fb_a_y = initObj.fb_a_y
      }
      else {
        this.fb_a_y = 0.0;
      }
      if (initObj.hasOwnProperty('fb_a_z')) {
        this.fb_a_z = initObj.fb_a_z
      }
      else {
        this.fb_a_z = 0.0;
      }
      if (initObj.hasOwnProperty('des_a_x')) {
        this.des_a_x = initObj.des_a_x
      }
      else {
        this.des_a_x = 0.0;
      }
      if (initObj.hasOwnProperty('des_a_y')) {
        this.des_a_y = initObj.des_a_y
      }
      else {
        this.des_a_y = 0.0;
      }
      if (initObj.hasOwnProperty('des_a_z')) {
        this.des_a_z = initObj.des_a_z
      }
      else {
        this.des_a_z = 0.0;
      }
      if (initObj.hasOwnProperty('des_q_x')) {
        this.des_q_x = initObj.des_q_x
      }
      else {
        this.des_q_x = 0.0;
      }
      if (initObj.hasOwnProperty('des_q_y')) {
        this.des_q_y = initObj.des_q_y
      }
      else {
        this.des_q_y = 0.0;
      }
      if (initObj.hasOwnProperty('des_q_z')) {
        this.des_q_z = initObj.des_q_z
      }
      else {
        this.des_q_z = 0.0;
      }
      if (initObj.hasOwnProperty('des_q_w')) {
        this.des_q_w = initObj.des_q_w
      }
      else {
        this.des_q_w = 0.0;
      }
      if (initObj.hasOwnProperty('des_thr')) {
        this.des_thr = initObj.des_thr
      }
      else {
        this.des_thr = 0.0;
      }
      if (initObj.hasOwnProperty('hover_percentage')) {
        this.hover_percentage = initObj.hover_percentage
      }
      else {
        this.hover_percentage = 0.0;
      }
      if (initObj.hasOwnProperty('thr_scale_compensate')) {
        this.thr_scale_compensate = initObj.thr_scale_compensate
      }
      else {
        this.thr_scale_compensate = 0.0;
      }
      if (initObj.hasOwnProperty('voltage')) {
        this.voltage = initObj.voltage
      }
      else {
        this.voltage = 0.0;
      }
      if (initObj.hasOwnProperty('err_axisang_x')) {
        this.err_axisang_x = initObj.err_axisang_x
      }
      else {
        this.err_axisang_x = 0.0;
      }
      if (initObj.hasOwnProperty('err_axisang_y')) {
        this.err_axisang_y = initObj.err_axisang_y
      }
      else {
        this.err_axisang_y = 0.0;
      }
      if (initObj.hasOwnProperty('err_axisang_z')) {
        this.err_axisang_z = initObj.err_axisang_z
      }
      else {
        this.err_axisang_z = 0.0;
      }
      if (initObj.hasOwnProperty('err_axisang_ang')) {
        this.err_axisang_ang = initObj.err_axisang_ang
      }
      else {
        this.err_axisang_ang = 0.0;
      }
      if (initObj.hasOwnProperty('fb_rate_x')) {
        this.fb_rate_x = initObj.fb_rate_x
      }
      else {
        this.fb_rate_x = 0.0;
      }
      if (initObj.hasOwnProperty('fb_rate_y')) {
        this.fb_rate_y = initObj.fb_rate_y
      }
      else {
        this.fb_rate_y = 0.0;
      }
      if (initObj.hasOwnProperty('fb_rate_z')) {
        this.fb_rate_z = initObj.fb_rate_z
      }
      else {
        this.fb_rate_z = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Px4ctrlDebug
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [des_v_x]
    bufferOffset = _serializer.float64(obj.des_v_x, buffer, bufferOffset);
    // Serialize message field [des_v_y]
    bufferOffset = _serializer.float64(obj.des_v_y, buffer, bufferOffset);
    // Serialize message field [des_v_z]
    bufferOffset = _serializer.float64(obj.des_v_z, buffer, bufferOffset);
    // Serialize message field [fb_a_x]
    bufferOffset = _serializer.float64(obj.fb_a_x, buffer, bufferOffset);
    // Serialize message field [fb_a_y]
    bufferOffset = _serializer.float64(obj.fb_a_y, buffer, bufferOffset);
    // Serialize message field [fb_a_z]
    bufferOffset = _serializer.float64(obj.fb_a_z, buffer, bufferOffset);
    // Serialize message field [des_a_x]
    bufferOffset = _serializer.float64(obj.des_a_x, buffer, bufferOffset);
    // Serialize message field [des_a_y]
    bufferOffset = _serializer.float64(obj.des_a_y, buffer, bufferOffset);
    // Serialize message field [des_a_z]
    bufferOffset = _serializer.float64(obj.des_a_z, buffer, bufferOffset);
    // Serialize message field [des_q_x]
    bufferOffset = _serializer.float64(obj.des_q_x, buffer, bufferOffset);
    // Serialize message field [des_q_y]
    bufferOffset = _serializer.float64(obj.des_q_y, buffer, bufferOffset);
    // Serialize message field [des_q_z]
    bufferOffset = _serializer.float64(obj.des_q_z, buffer, bufferOffset);
    // Serialize message field [des_q_w]
    bufferOffset = _serializer.float64(obj.des_q_w, buffer, bufferOffset);
    // Serialize message field [des_thr]
    bufferOffset = _serializer.float64(obj.des_thr, buffer, bufferOffset);
    // Serialize message field [hover_percentage]
    bufferOffset = _serializer.float64(obj.hover_percentage, buffer, bufferOffset);
    // Serialize message field [thr_scale_compensate]
    bufferOffset = _serializer.float64(obj.thr_scale_compensate, buffer, bufferOffset);
    // Serialize message field [voltage]
    bufferOffset = _serializer.float64(obj.voltage, buffer, bufferOffset);
    // Serialize message field [err_axisang_x]
    bufferOffset = _serializer.float64(obj.err_axisang_x, buffer, bufferOffset);
    // Serialize message field [err_axisang_y]
    bufferOffset = _serializer.float64(obj.err_axisang_y, buffer, bufferOffset);
    // Serialize message field [err_axisang_z]
    bufferOffset = _serializer.float64(obj.err_axisang_z, buffer, bufferOffset);
    // Serialize message field [err_axisang_ang]
    bufferOffset = _serializer.float64(obj.err_axisang_ang, buffer, bufferOffset);
    // Serialize message field [fb_rate_x]
    bufferOffset = _serializer.float64(obj.fb_rate_x, buffer, bufferOffset);
    // Serialize message field [fb_rate_y]
    bufferOffset = _serializer.float64(obj.fb_rate_y, buffer, bufferOffset);
    // Serialize message field [fb_rate_z]
    bufferOffset = _serializer.float64(obj.fb_rate_z, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Px4ctrlDebug
    let len;
    let data = new Px4ctrlDebug(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [des_v_x]
    data.des_v_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [des_v_y]
    data.des_v_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [des_v_z]
    data.des_v_z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fb_a_x]
    data.fb_a_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fb_a_y]
    data.fb_a_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fb_a_z]
    data.fb_a_z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [des_a_x]
    data.des_a_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [des_a_y]
    data.des_a_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [des_a_z]
    data.des_a_z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [des_q_x]
    data.des_q_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [des_q_y]
    data.des_q_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [des_q_z]
    data.des_q_z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [des_q_w]
    data.des_q_w = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [des_thr]
    data.des_thr = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [hover_percentage]
    data.hover_percentage = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [thr_scale_compensate]
    data.thr_scale_compensate = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [voltage]
    data.voltage = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [err_axisang_x]
    data.err_axisang_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [err_axisang_y]
    data.err_axisang_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [err_axisang_z]
    data.err_axisang_z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [err_axisang_ang]
    data.err_axisang_ang = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fb_rate_x]
    data.fb_rate_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fb_rate_y]
    data.fb_rate_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fb_rate_z]
    data.fb_rate_z = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 192;
  }

  static datatype() {
    // Returns string type for a message object
    return 'quadrotor_msgs/Px4ctrlDebug';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8adafd9362e5a8fc6c85e6f460fbfc53';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    float64 des_v_x
    float64 des_v_y
    float64 des_v_z
    
    float64 fb_a_x
    float64 fb_a_y
    float64 fb_a_z
    
    float64 des_a_x
    float64 des_a_y
    float64 des_a_z
    
    float64 des_q_x
    float64 des_q_y
    float64 des_q_z
    float64 des_q_w
    
    float64 des_thr
    float64 hover_percentage
    float64 thr_scale_compensate
    float64 voltage
    
    float64 err_axisang_x
    float64 err_axisang_y
    float64 err_axisang_z
    float64 err_axisang_ang
    
    float64 fb_rate_x
    float64 fb_rate_y
    float64 fb_rate_z
    
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Px4ctrlDebug(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.des_v_x !== undefined) {
      resolved.des_v_x = msg.des_v_x;
    }
    else {
      resolved.des_v_x = 0.0
    }

    if (msg.des_v_y !== undefined) {
      resolved.des_v_y = msg.des_v_y;
    }
    else {
      resolved.des_v_y = 0.0
    }

    if (msg.des_v_z !== undefined) {
      resolved.des_v_z = msg.des_v_z;
    }
    else {
      resolved.des_v_z = 0.0
    }

    if (msg.fb_a_x !== undefined) {
      resolved.fb_a_x = msg.fb_a_x;
    }
    else {
      resolved.fb_a_x = 0.0
    }

    if (msg.fb_a_y !== undefined) {
      resolved.fb_a_y = msg.fb_a_y;
    }
    else {
      resolved.fb_a_y = 0.0
    }

    if (msg.fb_a_z !== undefined) {
      resolved.fb_a_z = msg.fb_a_z;
    }
    else {
      resolved.fb_a_z = 0.0
    }

    if (msg.des_a_x !== undefined) {
      resolved.des_a_x = msg.des_a_x;
    }
    else {
      resolved.des_a_x = 0.0
    }

    if (msg.des_a_y !== undefined) {
      resolved.des_a_y = msg.des_a_y;
    }
    else {
      resolved.des_a_y = 0.0
    }

    if (msg.des_a_z !== undefined) {
      resolved.des_a_z = msg.des_a_z;
    }
    else {
      resolved.des_a_z = 0.0
    }

    if (msg.des_q_x !== undefined) {
      resolved.des_q_x = msg.des_q_x;
    }
    else {
      resolved.des_q_x = 0.0
    }

    if (msg.des_q_y !== undefined) {
      resolved.des_q_y = msg.des_q_y;
    }
    else {
      resolved.des_q_y = 0.0
    }

    if (msg.des_q_z !== undefined) {
      resolved.des_q_z = msg.des_q_z;
    }
    else {
      resolved.des_q_z = 0.0
    }

    if (msg.des_q_w !== undefined) {
      resolved.des_q_w = msg.des_q_w;
    }
    else {
      resolved.des_q_w = 0.0
    }

    if (msg.des_thr !== undefined) {
      resolved.des_thr = msg.des_thr;
    }
    else {
      resolved.des_thr = 0.0
    }

    if (msg.hover_percentage !== undefined) {
      resolved.hover_percentage = msg.hover_percentage;
    }
    else {
      resolved.hover_percentage = 0.0
    }

    if (msg.thr_scale_compensate !== undefined) {
      resolved.thr_scale_compensate = msg.thr_scale_compensate;
    }
    else {
      resolved.thr_scale_compensate = 0.0
    }

    if (msg.voltage !== undefined) {
      resolved.voltage = msg.voltage;
    }
    else {
      resolved.voltage = 0.0
    }

    if (msg.err_axisang_x !== undefined) {
      resolved.err_axisang_x = msg.err_axisang_x;
    }
    else {
      resolved.err_axisang_x = 0.0
    }

    if (msg.err_axisang_y !== undefined) {
      resolved.err_axisang_y = msg.err_axisang_y;
    }
    else {
      resolved.err_axisang_y = 0.0
    }

    if (msg.err_axisang_z !== undefined) {
      resolved.err_axisang_z = msg.err_axisang_z;
    }
    else {
      resolved.err_axisang_z = 0.0
    }

    if (msg.err_axisang_ang !== undefined) {
      resolved.err_axisang_ang = msg.err_axisang_ang;
    }
    else {
      resolved.err_axisang_ang = 0.0
    }

    if (msg.fb_rate_x !== undefined) {
      resolved.fb_rate_x = msg.fb_rate_x;
    }
    else {
      resolved.fb_rate_x = 0.0
    }

    if (msg.fb_rate_y !== undefined) {
      resolved.fb_rate_y = msg.fb_rate_y;
    }
    else {
      resolved.fb_rate_y = 0.0
    }

    if (msg.fb_rate_z !== undefined) {
      resolved.fb_rate_z = msg.fb_rate_z;
    }
    else {
      resolved.fb_rate_z = 0.0
    }

    return resolved;
    }
};

module.exports = Px4ctrlDebug;
