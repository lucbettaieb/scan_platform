cmake_minimum_required(VERSION 2.8.3)
project(ros_stepper_scan)

find_package(PCL 1.7 REQUIRED)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  angles
  message_generation
  pcl_ros
  pcl_conversions
)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)

# Generate services in the 'srv' folder
add_service_files(
  FILES
  stepper_scan.srv
)

# Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp sensor_msgs std_msgs angles
  DEPENDS system_lib
)


## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

add_definitions(${PCL_DEFINITIONS})

add_library(kinect2_interface src/kinect2_interface.cpp)
target_link_libraries(kinect2_interface ${PCL_LIBRARIES})

## Declare a C++ executable
add_executable(stepper_scan src/stepper_scan.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(stepper_scan ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(stepper_scan
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
  kinect2_interface
)
