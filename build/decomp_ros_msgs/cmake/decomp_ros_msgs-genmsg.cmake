# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "decomp_ros_msgs: 4 messages, 0 services")

set(MSG_I_FLAGS "-Idecomp_ros_msgs:/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(decomp_ros_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg" NAME_WE)
add_custom_target(_decomp_ros_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "decomp_ros_msgs" "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg" ""
)

get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/EllipsoidArray.msg" NAME_WE)
add_custom_target(_decomp_ros_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "decomp_ros_msgs" "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/EllipsoidArray.msg" "std_msgs/Header:decomp_ros_msgs/Ellipsoid"
)

get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg" NAME_WE)
add_custom_target(_decomp_ros_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "decomp_ros_msgs" "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg" "geometry_msgs/Point"
)

get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/PolyhedronArray.msg" NAME_WE)
add_custom_target(_decomp_ros_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "decomp_ros_msgs" "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/PolyhedronArray.msg" "std_msgs/Header:decomp_ros_msgs/Polyhedron:geometry_msgs/Point"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_cpp(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/EllipsoidArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_cpp(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_cpp(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/PolyhedronArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/decomp_ros_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(decomp_ros_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/decomp_ros_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(decomp_ros_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(decomp_ros_msgs_generate_messages decomp_ros_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_cpp _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/EllipsoidArray.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_cpp _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_cpp _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/PolyhedronArray.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_cpp _decomp_ros_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(decomp_ros_msgs_gencpp)
add_dependencies(decomp_ros_msgs_gencpp decomp_ros_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS decomp_ros_msgs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_eus(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/EllipsoidArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_eus(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_eus(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/PolyhedronArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/decomp_ros_msgs
)

### Generating Services

### Generating Module File
_generate_module_eus(decomp_ros_msgs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/decomp_ros_msgs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(decomp_ros_msgs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(decomp_ros_msgs_generate_messages decomp_ros_msgs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_eus _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/EllipsoidArray.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_eus _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_eus _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/PolyhedronArray.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_eus _decomp_ros_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(decomp_ros_msgs_geneus)
add_dependencies(decomp_ros_msgs_geneus decomp_ros_msgs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS decomp_ros_msgs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_lisp(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/EllipsoidArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_lisp(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_lisp(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/PolyhedronArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/decomp_ros_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(decomp_ros_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/decomp_ros_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(decomp_ros_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(decomp_ros_msgs_generate_messages decomp_ros_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_lisp _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/EllipsoidArray.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_lisp _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_lisp _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/PolyhedronArray.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_lisp _decomp_ros_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(decomp_ros_msgs_genlisp)
add_dependencies(decomp_ros_msgs_genlisp decomp_ros_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS decomp_ros_msgs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_nodejs(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/EllipsoidArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_nodejs(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_nodejs(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/PolyhedronArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/decomp_ros_msgs
)

### Generating Services

### Generating Module File
_generate_module_nodejs(decomp_ros_msgs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/decomp_ros_msgs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(decomp_ros_msgs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(decomp_ros_msgs_generate_messages decomp_ros_msgs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_nodejs _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/EllipsoidArray.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_nodejs _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_nodejs _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/PolyhedronArray.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_nodejs _decomp_ros_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(decomp_ros_msgs_gennodejs)
add_dependencies(decomp_ros_msgs_gennodejs decomp_ros_msgs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS decomp_ros_msgs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_py(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/EllipsoidArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_py(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/decomp_ros_msgs
)
_generate_msg_py(decomp_ros_msgs
  "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/PolyhedronArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/decomp_ros_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(decomp_ros_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/decomp_ros_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(decomp_ros_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(decomp_ros_msgs_generate_messages decomp_ros_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Ellipsoid.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_py _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/EllipsoidArray.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_py _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/Polyhedron.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_py _decomp_ros_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/xingxun/experiment/Fast-Exploration/src/Utils/DecompROS/decomp_ros_msgs/msg/PolyhedronArray.msg" NAME_WE)
add_dependencies(decomp_ros_msgs_generate_messages_py _decomp_ros_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(decomp_ros_msgs_genpy)
add_dependencies(decomp_ros_msgs_genpy decomp_ros_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS decomp_ros_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/decomp_ros_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/decomp_ros_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(decomp_ros_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/decomp_ros_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/decomp_ros_msgs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(decomp_ros_msgs_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/decomp_ros_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/decomp_ros_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(decomp_ros_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/decomp_ros_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/decomp_ros_msgs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(decomp_ros_msgs_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/decomp_ros_msgs)
  install(CODE "execute_process(COMMAND \"/home/xingxun/miniconda3/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/decomp_ros_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/decomp_ros_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(decomp_ros_msgs_generate_messages_py geometry_msgs_generate_messages_py)
endif()
