# cmake_minimum_required(VERSION 3.5)
# project(motion_cmd)

# # Default to C++14
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Suppress warnings treated as errors in GTest
# if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#   add_compile_options(-Wno-error=maybe-uninitialized)
# endif()

# # Find dependencies
# find_package(ament_cmake REQUIRED)
# find_package(rclcpp REQUIRED)
# find_package(std_msgs REQUIRED)
# find_package(geometry_msgs REQUIRED)
# find_package(tf2 REQUIRED)
# find_package(tf2_ros REQUIRED)
# find_package(tf2_geometry_msgs REQUIRED)
# find_package(tf2_eigen REQUIRED)
# find_package(i2cpwm_controller REQUIRED)
# find_package(eigen3_cmake_module REQUIRED)
# find_package(Eigen3 REQUIRED)

# # Add subdirectory for external libraries like spot_micro_kinematics_cpp
# add_subdirectory(libs/spot_micro_kinematics_cpp)

# link_directories(/opt/ros/humble/lib)

# # Include directories
# include_directories(
#   include/motion_cmd
#   src/smfsm
#   src/rate_limited_first_order_filter
#   ${EIGEN3_INCLUDE_DIRS}
# )

# # Declare the library for the state machine (smfsm)
# add_library(smfsm 
#   src/smfsm/state.cpp 
#   src/smfsm/idle.cpp
#   src/smfsm/stand.cpp
#   src/smfsm/transition_stand.cpp
#   src/smfsm/transition_idle.cpp
#   src/smfsm/walk.cpp
# )

# # Link the state machine library with the kinematics library
# target_link_libraries(smfsm
#   spot_micro_kinematics
#   i2cpwm_controller_lib
#   tf2::tf2
#   tf2_ros::tf2_ros
#   tf2_geometry_msgs::tf2_geometry_msgs
#   tf2_eigen_kdl
#   Eigen3::Eigen
# )

# # Specify dependencies using ament_target_dependencies
# ament_target_dependencies(smfsm
#   rclcpp
#   i2cpwm_controller
#   std_msgs
#   geometry_msgs
#   tf2
#   tf2_ros
#   tf2_geometry_msgs
#   tf2_eigen
# )

# # Add the executable for the SpotMicroMotionCmd node
# add_executable(motion_cmd_node
#   src/motion_cmd.cpp
#   src/main.cpp
#   src/utils.cpp
# )

# # Link the executable to required libraries
# target_link_libraries(motion_cmd_node
#   smfsm
#   spot_micro_kinematics
#   i2cpwm_controller_lib
#   tf2::tf2
#   tf2_ros::tf2_ros
#   tf2_geometry_msgs::tf2_geometry_msgs
#   tf2_eigen_kdl
#   Eigen3::EigenA
# )

# # Specify dependencies using ament_target_dependencies
# ament_target_dependencies(motion_cmd_node
#   rclcpp
#   i2cpwm_controller
#   std_msgs
#   geometry_msgs
#   tf2
#   tf2_ros
#   tf2_geometry_msgs
#   tf2_eigen
# )

# # Install targets
# install(TARGETS
#   motion_cmd_node
#   DESTINATION lib/${PROJECT_NAME}
# )

# # Install launch files and config files
# install(DIRECTORY launch config
#   DESTINATION share/${PROJECT_NAME}
# )

# # Export package dependencies
# ament_export_dependencies(rclcpp i2cpwm_controller std_msgs geometry_msgs tf2 tf2_ros tf2_geometry_msgs tf2_eigen Eigen3)
# ament_package()

cmake_minimum_required(VERSION 3.5)
project(motion_cmd)

# Default to C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Suppress warnings treated as errors in GTest
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(-Wno-error=maybe-uninitialized)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_eigen REQUIRED)
find_package(i2cpwm_controller REQUIRED)
find_package(eigen3_cmake_module REQUIRED)
find_package(Eigen3 REQUIRED)

# Add subdirectory for spot_micro_kinematics_cpp library
add_subdirectory(libs/spot_micro_kinematics_cpp)

# Include directories
include_directories(
  include/motion_cmd
  src/smfsm
  src/rate_limited_first_order_filter
  libs/spot_micro_kinematics_cpp/include
  ${EIGEN3_INCLUDE_DIRS}
)

# Declare the library for the state machine (smfsm)
add_library(smfsm 
  src/smfsm/state.cpp 
  src/smfsm/idle.cpp
  src/smfsm/stand.cpp
  src/smfsm/transition_stand.cpp
  src/smfsm/transition_idle.cpp
  src/smfsm/walk.cpp
)

# Link the state machine library with spot_micro_kinematics and other dependencies
target_link_libraries(smfsm
  spot_micro_kinematics  # Link the custom library
  tf2::tf2
  tf2_ros::tf2_ros
  tf2_geometry_msgs::tf2_geometry_msgs
  # tf2_eigen_kdl
  Eigen3::Eigen
)

# Specify dependencies for smfsm
ament_target_dependencies(smfsm
  rclcpp
  i2cpwm_controller
  std_msgs
  geometry_msgs
  tf2
  tf2_ros
  tf2_geometry_msgs
  tf2_eigen
  Eigen3
)

# Add the executable for the SpotMicroMotionCmd node
add_executable(motion_cmd_node
  src/motion_cmd.cpp
  src/main.cpp
  src/utils.cpp
)

# Link the executable to smfsm, spot_micro_kinematics, and other dependencies
target_link_libraries(motion_cmd_node
  smfsm
  spot_micro_kinematics  # Link the custom library here as well
  tf2::tf2
  tf2_ros::tf2_ros
  tf2_geometry_msgs::tf2_geometry_msgs
  # tf2_eigen_kdl
  Eigen3::Eigen
)

# Specify dependencies for the executable
ament_target_dependencies(motion_cmd_node
  rclcpp
  i2cpwm_controller
  std_msgs
  geometry_msgs
  tf2
  tf2_ros
  tf2_geometry_msgs
  tf2_eigen
  Eigen3
)

# Install targets
install(TARGETS
  motion_cmd_node
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files and config files
install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

# Export package dependencies
ament_export_dependencies(rclcpp i2cpwm_controller std_msgs geometry_msgs tf2 tf2_ros tf2_geometry_msgs tf2_eigen Eigen3)
ament_package()
