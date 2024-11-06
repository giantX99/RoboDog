# CMake generated Testfile for 
# Source directory: /home/robodog/RoboDog/ros2_ws/src/motion_cmd/libs/spot_micro_kinematics_cpp
# Build directory: /home/robodog/RoboDog/ros2_ws/build/motion_cmd/libs/spot_micro_kinematics_cpp
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_utils "test_utils")
set_tests_properties(test_utils PROPERTIES  _BACKTRACE_TRIPLES "/home/robodog/RoboDog/ros2_ws/src/motion_cmd/libs/spot_micro_kinematics_cpp/CMakeLists.txt;46;add_test;/home/robodog/RoboDog/ros2_ws/src/motion_cmd/libs/spot_micro_kinematics_cpp/CMakeLists.txt;0;")
add_test(test_spot_micro_leg "test_spot_micro_leg")
set_tests_properties(test_spot_micro_leg PROPERTIES  _BACKTRACE_TRIPLES "/home/robodog/RoboDog/ros2_ws/src/motion_cmd/libs/spot_micro_kinematics_cpp/CMakeLists.txt;58;add_test;/home/robodog/RoboDog/ros2_ws/src/motion_cmd/libs/spot_micro_kinematics_cpp/CMakeLists.txt;0;")
add_test(test_spot_micro_kinematics "test_spot_micro_kinematics")
set_tests_properties(test_spot_micro_kinematics PROPERTIES  _BACKTRACE_TRIPLES "/home/robodog/RoboDog/ros2_ws/src/motion_cmd/libs/spot_micro_kinematics_cpp/CMakeLists.txt;69;add_test;/home/robodog/RoboDog/ros2_ws/src/motion_cmd/libs/spot_micro_kinematics_cpp/CMakeLists.txt;0;")
subdirs("3rd_party/google-test")
