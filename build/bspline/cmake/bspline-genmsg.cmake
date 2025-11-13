# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "bspline: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ibspline:/home/xingxun/experiment/Fast-Exploration/src/fuel_planner/bspline/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(bspline_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/fuel_planner/bspline/msg/Bspline.msg" NAME_WE)
add_custom_target(_bspline_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "bspline" "/home/xingxun/experiment/Fast-Exploration/src/fuel_planner/bspline/msg/Bspline.msg" "geometry_msgs/Point"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(bspline
  "/home/xingxun/experiment/Fast-Exploration/src/fuel_planner/bspline/msg/Bspline.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bspline
)

### Generating Services

### Generating Module File
_generate_module_cpp(bspline
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bspline
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(bspline_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(bspline_generate_messages bspline_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/fuel_planner/bspline/msg/Bspline.msg" NAME_WE)
add_dependencies(bspline_generate_messages_cpp _bspline_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bspline_gencpp)
add_dependencies(bspline_gencpp bspline_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bspline_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(bspline
  "/home/xingxun/experiment/Fast-Exploration/src/fuel_planner/bspline/msg/Bspline.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/bspline
)

### Generating Services

### Generating Module File
_generate_module_eus(bspline
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/bspline
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(bspline_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(bspline_generate_messages bspline_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/fuel_planner/bspline/msg/Bspline.msg" NAME_WE)
add_dependencies(bspline_generate_messages_eus _bspline_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bspline_geneus)
add_dependencies(bspline_geneus bspline_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bspline_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(bspline
  "/home/xingxun/experiment/Fast-Exploration/src/fuel_planner/bspline/msg/Bspline.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bspline
)

### Generating Services

### Generating Module File
_generate_module_lisp(bspline
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bspline
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(bspline_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(bspline_generate_messages bspline_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/fuel_planner/bspline/msg/Bspline.msg" NAME_WE)
add_dependencies(bspline_generate_messages_lisp _bspline_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bspline_genlisp)
add_dependencies(bspline_genlisp bspline_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bspline_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(bspline
  "/home/xingxun/experiment/Fast-Exploration/src/fuel_planner/bspline/msg/Bspline.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/bspline
)

### Generating Services

### Generating Module File
_generate_module_nodejs(bspline
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/bspline
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(bspline_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(bspline_generate_messages bspline_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/fuel_planner/bspline/msg/Bspline.msg" NAME_WE)
add_dependencies(bspline_generate_messages_nodejs _bspline_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bspline_gennodejs)
add_dependencies(bspline_gennodejs bspline_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bspline_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(bspline
  "/home/xingxun/experiment/Fast-Exploration/src/fuel_planner/bspline/msg/Bspline.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bspline
)

### Generating Services

### Generating Module File
_generate_module_py(bspline
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bspline
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(bspline_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(bspline_generate_messages bspline_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/fuel_planner/bspline/msg/Bspline.msg" NAME_WE)
add_dependencies(bspline_generate_messages_py _bspline_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bspline_genpy)
add_dependencies(bspline_genpy bspline_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bspline_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bspline)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bspline
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(bspline_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(bspline_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/bspline)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/bspline
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(bspline_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(bspline_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bspline)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bspline
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(bspline_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(bspline_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/bspline)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/bspline
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(bspline_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(bspline_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bspline)
  install(CODE "execute_process(COMMAND \"/home/xingxun/miniconda3/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bspline\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bspline
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(bspline_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(bspline_generate_messages_py geometry_msgs_generate_messages_py)
endif()
