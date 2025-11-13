cmake_minimum_required(VERSION 2.8.3)
project(corridor_generator)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-O3 -Wall -g")
ADD_COMPILE_OPTIONS(-std=c++11)
ADD_COMPILE_OPTIONS(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  nav_msgs
  sensor_msgs
  visualization_msgs
  decomp_ros_msgs
  decomp_ros_utils
  tf
)

find_package(Eigen3 REQUIRED)
find_package(PCL REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp rospy std_msgs geometry_msgs nav_msgs sensor_msgs visualization_msgs decomp_ros_msgs decomp_ros_utils tf
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/../../fuel_planner/DecompROS/decomp_ros_utils/include
)

add_executable(corridor_generator_node 
  src/corridor_generator_node.cpp
)

target_link_libraries(corridor_generator_node
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
)

add_dependencies(corridor_generator_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

