# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/robodog/RoboDog/ros2_ws/src/motion_cmd

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robodog/RoboDog/ros2_ws/build/motion_cmd

# Include any dependencies generated for this target.
include CMakeFiles/motion_cmd_node.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/motion_cmd_node.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/motion_cmd_node.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/motion_cmd_node.dir/flags.make

CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.o: CMakeFiles/motion_cmd_node.dir/flags.make
CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.o: /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/motion_cmd.cpp
CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.o: CMakeFiles/motion_cmd_node.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robodog/RoboDog/ros2_ws/build/motion_cmd/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.o -MF CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.o.d -o CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.o -c /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/motion_cmd.cpp

CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/motion_cmd.cpp > CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.i

CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/motion_cmd.cpp -o CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.s

CMakeFiles/motion_cmd_node.dir/src/main.cpp.o: CMakeFiles/motion_cmd_node.dir/flags.make
CMakeFiles/motion_cmd_node.dir/src/main.cpp.o: /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/main.cpp
CMakeFiles/motion_cmd_node.dir/src/main.cpp.o: CMakeFiles/motion_cmd_node.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robodog/RoboDog/ros2_ws/build/motion_cmd/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/motion_cmd_node.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/motion_cmd_node.dir/src/main.cpp.o -MF CMakeFiles/motion_cmd_node.dir/src/main.cpp.o.d -o CMakeFiles/motion_cmd_node.dir/src/main.cpp.o -c /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/main.cpp

CMakeFiles/motion_cmd_node.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/motion_cmd_node.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/main.cpp > CMakeFiles/motion_cmd_node.dir/src/main.cpp.i

CMakeFiles/motion_cmd_node.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/motion_cmd_node.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/main.cpp -o CMakeFiles/motion_cmd_node.dir/src/main.cpp.s

CMakeFiles/motion_cmd_node.dir/src/utils.cpp.o: CMakeFiles/motion_cmd_node.dir/flags.make
CMakeFiles/motion_cmd_node.dir/src/utils.cpp.o: /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/utils.cpp
CMakeFiles/motion_cmd_node.dir/src/utils.cpp.o: CMakeFiles/motion_cmd_node.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robodog/RoboDog/ros2_ws/build/motion_cmd/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/motion_cmd_node.dir/src/utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/motion_cmd_node.dir/src/utils.cpp.o -MF CMakeFiles/motion_cmd_node.dir/src/utils.cpp.o.d -o CMakeFiles/motion_cmd_node.dir/src/utils.cpp.o -c /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/utils.cpp

CMakeFiles/motion_cmd_node.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/motion_cmd_node.dir/src/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/utils.cpp > CMakeFiles/motion_cmd_node.dir/src/utils.cpp.i

CMakeFiles/motion_cmd_node.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/motion_cmd_node.dir/src/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/utils.cpp -o CMakeFiles/motion_cmd_node.dir/src/utils.cpp.s

# Object files for target motion_cmd_node
motion_cmd_node_OBJECTS = \
"CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.o" \
"CMakeFiles/motion_cmd_node.dir/src/main.cpp.o" \
"CMakeFiles/motion_cmd_node.dir/src/utils.cpp.o"

# External object files for target motion_cmd_node
motion_cmd_node_EXTERNAL_OBJECTS =

motion_cmd_node: CMakeFiles/motion_cmd_node.dir/src/motion_cmd.cpp.o
motion_cmd_node: CMakeFiles/motion_cmd_node.dir/src/main.cpp.o
motion_cmd_node: CMakeFiles/motion_cmd_node.dir/src/utils.cpp.o
motion_cmd_node: CMakeFiles/motion_cmd_node.dir/build.make
motion_cmd_node: libsmfsm.a
motion_cmd_node: libs/spot_micro_kinematics_cpp/libspot_micro_kinematics.a
motion_cmd_node: /home/robodog/RoboDog/ros2_ws/install/i2cpwm_controller/lib/libi2cpwm_controller__rosidl_typesupport_fastrtps_c.so
motion_cmd_node: /home/robodog/RoboDog/ros2_ws/install/i2cpwm_controller/lib/libi2cpwm_controller__rosidl_typesupport_fastrtps_cpp.so
motion_cmd_node: /home/robodog/RoboDog/ros2_ws/install/i2cpwm_controller/lib/libi2cpwm_controller__rosidl_typesupport_introspection_c.so
motion_cmd_node: /home/robodog/RoboDog/ros2_ws/install/i2cpwm_controller/lib/libi2cpwm_controller__rosidl_typesupport_introspection_cpp.so
motion_cmd_node: /home/robodog/RoboDog/ros2_ws/install/i2cpwm_controller/lib/libi2cpwm_controller__rosidl_generator_py.so
motion_cmd_node: /home/robodog/RoboDog/ros2_ws/install/i2cpwm_controller/lib/libi2cpwm_controller_lib.so
motion_cmd_node: /opt/ros/humble/lib/libstatic_transform_broadcaster_node.so
motion_cmd_node: /usr/lib/aarch64-linux-gnu/liborocos-kdl.so
motion_cmd_node: /home/robodog/RoboDog/ros2_ws/install/i2cpwm_controller/lib/libi2cpwm_controller__rosidl_typesupport_c.so
motion_cmd_node: /home/robodog/RoboDog/ros2_ws/install/i2cpwm_controller/lib/libi2cpwm_controller__rosidl_generator_c.so
motion_cmd_node: /home/robodog/RoboDog/ros2_ws/install/i2cpwm_controller/lib/libi2cpwm_controller__rosidl_typesupport_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libstd_srvs__rosidl_typesupport_fastrtps_c.so
motion_cmd_node: /opt/ros/humble/lib/libstd_srvs__rosidl_typesupport_fastrtps_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libstd_srvs__rosidl_typesupport_introspection_c.so
motion_cmd_node: /opt/ros/humble/lib/libstd_srvs__rosidl_typesupport_introspection_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libstd_srvs__rosidl_typesupport_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libstd_srvs__rosidl_generator_py.so
motion_cmd_node: /opt/ros/humble/lib/libstd_srvs__rosidl_typesupport_c.so
motion_cmd_node: /opt/ros/humble/lib/libstd_srvs__rosidl_generator_c.so
motion_cmd_node: /usr/lib/aarch64-linux-gnu/libi2c.so
motion_cmd_node: /opt/ros/humble/lib/libtf2_ros.so
motion_cmd_node: /opt/ros/humble/lib/libtf2.so
motion_cmd_node: /opt/ros/humble/lib/libmessage_filters.so
motion_cmd_node: /opt/ros/humble/lib/librclcpp_action.so
motion_cmd_node: /opt/ros/humble/lib/librclcpp.so
motion_cmd_node: /opt/ros/humble/lib/liblibstatistics_collector.so
motion_cmd_node: /opt/ros/humble/lib/librosgraph_msgs__rosidl_typesupport_fastrtps_c.so
motion_cmd_node: /opt/ros/humble/lib/librosgraph_msgs__rosidl_typesupport_fastrtps_cpp.so
motion_cmd_node: /opt/ros/humble/lib/librosgraph_msgs__rosidl_typesupport_introspection_c.so
motion_cmd_node: /opt/ros/humble/lib/librosgraph_msgs__rosidl_typesupport_introspection_cpp.so
motion_cmd_node: /opt/ros/humble/lib/librosgraph_msgs__rosidl_typesupport_cpp.so
motion_cmd_node: /opt/ros/humble/lib/librosgraph_msgs__rosidl_generator_py.so
motion_cmd_node: /opt/ros/humble/lib/librosgraph_msgs__rosidl_typesupport_c.so
motion_cmd_node: /opt/ros/humble/lib/librosgraph_msgs__rosidl_generator_c.so
motion_cmd_node: /opt/ros/humble/lib/libstatistics_msgs__rosidl_typesupport_fastrtps_c.so
motion_cmd_node: /opt/ros/humble/lib/libstatistics_msgs__rosidl_typesupport_fastrtps_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libstatistics_msgs__rosidl_typesupport_introspection_c.so
motion_cmd_node: /opt/ros/humble/lib/libstatistics_msgs__rosidl_typesupport_introspection_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libstatistics_msgs__rosidl_typesupport_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libstatistics_msgs__rosidl_generator_py.so
motion_cmd_node: /opt/ros/humble/lib/libstatistics_msgs__rosidl_typesupport_c.so
motion_cmd_node: /opt/ros/humble/lib/libstatistics_msgs__rosidl_generator_c.so
motion_cmd_node: /opt/ros/humble/lib/librcl_action.so
motion_cmd_node: /opt/ros/humble/lib/librcl.so
motion_cmd_node: /opt/ros/humble/lib/librcl_interfaces__rosidl_typesupport_fastrtps_c.so
motion_cmd_node: /opt/ros/humble/lib/librcl_interfaces__rosidl_typesupport_introspection_c.so
motion_cmd_node: /opt/ros/humble/lib/librcl_interfaces__rosidl_typesupport_fastrtps_cpp.so
motion_cmd_node: /opt/ros/humble/lib/librcl_interfaces__rosidl_typesupport_introspection_cpp.so
motion_cmd_node: /opt/ros/humble/lib/librcl_interfaces__rosidl_typesupport_cpp.so
motion_cmd_node: /opt/ros/humble/lib/librcl_interfaces__rosidl_generator_py.so
motion_cmd_node: /opt/ros/humble/lib/librcl_interfaces__rosidl_typesupport_c.so
motion_cmd_node: /opt/ros/humble/lib/librcl_interfaces__rosidl_generator_c.so
motion_cmd_node: /opt/ros/humble/lib/librcl_yaml_param_parser.so
motion_cmd_node: /opt/ros/humble/lib/libyaml.so
motion_cmd_node: /opt/ros/humble/lib/libtracetools.so
motion_cmd_node: /opt/ros/humble/lib/librmw_implementation.so
motion_cmd_node: /opt/ros/humble/lib/libament_index_cpp.so
motion_cmd_node: /opt/ros/humble/lib/librcl_logging_spdlog.so
motion_cmd_node: /opt/ros/humble/lib/librcl_logging_interface.so
motion_cmd_node: /opt/ros/humble/lib/libtf2_msgs__rosidl_typesupport_fastrtps_c.so
motion_cmd_node: /opt/ros/humble/lib/libaction_msgs__rosidl_typesupport_fastrtps_c.so
motion_cmd_node: /opt/ros/humble/lib/libunique_identifier_msgs__rosidl_typesupport_fastrtps_c.so
motion_cmd_node: /opt/ros/humble/lib/libtf2_msgs__rosidl_typesupport_introspection_c.so
motion_cmd_node: /opt/ros/humble/lib/libaction_msgs__rosidl_typesupport_introspection_c.so
motion_cmd_node: /opt/ros/humble/lib/libunique_identifier_msgs__rosidl_typesupport_introspection_c.so
motion_cmd_node: /opt/ros/humble/lib/libtf2_msgs__rosidl_typesupport_fastrtps_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libaction_msgs__rosidl_typesupport_fastrtps_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libunique_identifier_msgs__rosidl_typesupport_fastrtps_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libtf2_msgs__rosidl_typesupport_introspection_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libaction_msgs__rosidl_typesupport_introspection_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libunique_identifier_msgs__rosidl_typesupport_introspection_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libtf2_msgs__rosidl_typesupport_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libaction_msgs__rosidl_typesupport_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libunique_identifier_msgs__rosidl_typesupport_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libtf2_msgs__rosidl_generator_py.so
motion_cmd_node: /opt/ros/humble/lib/libtf2_msgs__rosidl_typesupport_c.so
motion_cmd_node: /opt/ros/humble/lib/libtf2_msgs__rosidl_generator_c.so
motion_cmd_node: /opt/ros/humble/lib/libaction_msgs__rosidl_generator_py.so
motion_cmd_node: /opt/ros/humble/lib/libaction_msgs__rosidl_typesupport_c.so
motion_cmd_node: /opt/ros/humble/lib/libaction_msgs__rosidl_generator_c.so
motion_cmd_node: /opt/ros/humble/lib/libunique_identifier_msgs__rosidl_generator_py.so
motion_cmd_node: /opt/ros/humble/lib/libunique_identifier_msgs__rosidl_typesupport_c.so
motion_cmd_node: /opt/ros/humble/lib/libunique_identifier_msgs__rosidl_generator_c.so
motion_cmd_node: /opt/ros/humble/lib/libgeometry_msgs__rosidl_typesupport_fastrtps_c.so
motion_cmd_node: /opt/ros/humble/lib/libstd_msgs__rosidl_typesupport_fastrtps_c.so
motion_cmd_node: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_typesupport_fastrtps_c.so
motion_cmd_node: /opt/ros/humble/lib/librosidl_typesupport_fastrtps_c.so
motion_cmd_node: /opt/ros/humble/lib/libgeometry_msgs__rosidl_typesupport_introspection_c.so
motion_cmd_node: /opt/ros/humble/lib/libstd_msgs__rosidl_typesupport_introspection_c.so
motion_cmd_node: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_c.so
motion_cmd_node: /opt/ros/humble/lib/libgeometry_msgs__rosidl_typesupport_fastrtps_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libstd_msgs__rosidl_typesupport_fastrtps_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_typesupport_fastrtps_cpp.so
motion_cmd_node: /opt/ros/humble/lib/librosidl_typesupport_fastrtps_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libfastcdr.so.1.0.24
motion_cmd_node: /opt/ros/humble/lib/librmw.so
motion_cmd_node: /opt/ros/humble/lib/libgeometry_msgs__rosidl_typesupport_introspection_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libstd_msgs__rosidl_typesupport_introspection_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_cpp.so
motion_cmd_node: /opt/ros/humble/lib/librosidl_typesupport_introspection_cpp.so
motion_cmd_node: /opt/ros/humble/lib/librosidl_typesupport_introspection_c.so
motion_cmd_node: /opt/ros/humble/lib/libgeometry_msgs__rosidl_typesupport_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libstd_msgs__rosidl_typesupport_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_typesupport_cpp.so
motion_cmd_node: /opt/ros/humble/lib/librosidl_typesupport_cpp.so
motion_cmd_node: /opt/ros/humble/lib/libgeometry_msgs__rosidl_generator_py.so
motion_cmd_node: /opt/ros/humble/lib/libstd_msgs__rosidl_generator_py.so
motion_cmd_node: /opt/ros/humble/lib/libgeometry_msgs__rosidl_typesupport_c.so
motion_cmd_node: /opt/ros/humble/lib/libstd_msgs__rosidl_typesupport_c.so
motion_cmd_node: /opt/ros/humble/lib/libgeometry_msgs__rosidl_generator_c.so
motion_cmd_node: /opt/ros/humble/lib/libstd_msgs__rosidl_generator_c.so
motion_cmd_node: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_generator_py.so
motion_cmd_node: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_typesupport_c.so
motion_cmd_node: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_generator_c.so
motion_cmd_node: /opt/ros/humble/lib/librosidl_typesupport_c.so
motion_cmd_node: /opt/ros/humble/lib/librcpputils.so
motion_cmd_node: /opt/ros/humble/lib/librosidl_runtime_c.so
motion_cmd_node: /opt/ros/humble/lib/librcutils.so
motion_cmd_node: /usr/lib/aarch64-linux-gnu/libpython3.10.so
motion_cmd_node: CMakeFiles/motion_cmd_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robodog/RoboDog/ros2_ws/build/motion_cmd/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable motion_cmd_node"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/motion_cmd_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/motion_cmd_node.dir/build: motion_cmd_node
.PHONY : CMakeFiles/motion_cmd_node.dir/build

CMakeFiles/motion_cmd_node.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/motion_cmd_node.dir/cmake_clean.cmake
.PHONY : CMakeFiles/motion_cmd_node.dir/clean

CMakeFiles/motion_cmd_node.dir/depend:
	cd /home/robodog/RoboDog/ros2_ws/build/motion_cmd && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robodog/RoboDog/ros2_ws/src/motion_cmd /home/robodog/RoboDog/ros2_ws/src/motion_cmd /home/robodog/RoboDog/ros2_ws/build/motion_cmd /home/robodog/RoboDog/ros2_ws/build/motion_cmd /home/robodog/RoboDog/ros2_ws/build/motion_cmd/CMakeFiles/motion_cmd_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/motion_cmd_node.dir/depend

