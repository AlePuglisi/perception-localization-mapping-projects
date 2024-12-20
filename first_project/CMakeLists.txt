cmake_minimum_required(VERSION 3.0.2)
project(first_project)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  tf
  nav_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  Odom.msg
 )

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   reset_odom.srv
 )

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
    std_msgs
 )

###################################
## catkin specific configuration ##
###################################

catkin_package(
CATKIN_DEPENDS message_runtime
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include ${catkin_INCLUDE_DIRS})

## Add cmake target dependencies of the executable
## same as for the library above
add_executable(odom_node src/odom_node.cpp)
add_dependencies(odom_node custom_messages_generate_messages_cpp)
target_link_libraries(odom_node ${catkin_LIBRARIES})

