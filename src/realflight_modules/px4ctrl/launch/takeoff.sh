#!/bin/bash

# Wait for some time (optional)
sleep 3

# Publish to the appropriate topic
rostopic pub /px4ctrl/takeoff_land quadrotor_msgs/TakeoffLand "takeoff_land_cmd: 1"
