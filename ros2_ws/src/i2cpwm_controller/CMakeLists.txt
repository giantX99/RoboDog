cmake_minimum_required(VERSION 3.5)
project(i2cpwm_controller)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rosidl_default_runtime REQUIRED)
find_package(geometry_msgs REQUIRED)

# Add i2c library
find_library(I2C_LIBRARY i2c REQUIRED)

# Define custom messages and services
set(msg_files
  "msg/Position.msg"
  "msg/PositionArray.msg"
  "msg/Servo.msg"
  "msg/ServoArray.msg"
  "msg/ServoConfig.msg"
  "msg/ServoConfigArray.msg"
)

set(srv_files
  "srv/DriveMode.srv"
  "srv/IntValue.srv"
  "srv/ServosConfig.srv"
  "srv/StopServos.srv"
)

# Generate ROS 2 interfaces (messages and services)
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  ${srv_files}
  DEPENDENCIES builtin_interfaces std_msgs std_srvs geometry_msgs
)

# Include directories
include_directories(
  include
  /usr/include
  ${rclcpp_INCLUDE_DIRS}
  ${std_msgs_INCLUDE_DIRS}
  ${std_srvs_INCLUDE_DIRS}
)

# Add executable for i2cpwm_controller
add_executable(i2cpwm_controller_node src/i2cpwm_controller.cpp src/main.cpp)

# Link libraries
ament_target_dependencies(i2cpwm_controller_node
  rclcpp
  std_msgs
  std_srvs
  geometry_msgs
)

# Link generated message/service libraries
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp
)
target_link_libraries(i2cpwm_controller_node "${cpp_typesupport_target}" ${I2C_LIBRARY})


# Install launch files
install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch
)

# Export package and targets
ament_export_dependencies(rosidl_default_runtime)
ament_export_dependencies(rosidl_default_runtime rclcpp std_msgs std_srvs geometry_msgs)
ament_package()
