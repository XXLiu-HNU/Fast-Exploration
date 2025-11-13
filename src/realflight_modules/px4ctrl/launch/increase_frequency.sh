#!/bin/bash
DRONE_ID=${DRONE_ID:-0} 
sleep 3
# Run the first rosrun command and wait 1 second
rosrun mavros mavcmd --mavros-ns /iris_${DRONE_ID}/mavros long 511 105 5000 0 0 0 0 0 & 
sleep 1

# Run the second rosrun command and wait 1 second
rosrun mavros mavcmd --mavros-ns /iris_${DRONE_ID}/mavros long 511 31 5000 0 0 0 0 0 & 
sleep 1
