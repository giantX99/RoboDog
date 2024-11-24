# Use this file in case ROS2 package motion_cmd is not being recognized by ROS.
# This will happen if motion_cmd path is currently not in $AMENT_PREFIX_PATH
# This file will execute the following bash line appending motion_cmd path manually:
export AMENT_PREFIX_PATH=/home/robodog/RoboDog/ros2_ws/install/motion_cmd:$AMENT_PREFIX_PATH

# Execute this file by typing:
# source /home/robodog/RoboDog/docs/motion_cmd_source.sh

# Then use "echo $AMENT_PREFIX_PATH" to check if motion_cmd path was added.