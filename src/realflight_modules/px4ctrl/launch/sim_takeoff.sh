#!/bin/bash

# Get the drone_id from the environment variable
DRONE_ID=${DRONE_ID:-0}  # Default to 0 if not set

# Wait for some time (optional)
sleep 3

# Publish to the appropriate topic
rostopic pub /iris_${DRONE_ID}_px4ctrl/takeoff_land quadrotor_msgs/TakeoffLand "takeoff_land_cmd: 1"
