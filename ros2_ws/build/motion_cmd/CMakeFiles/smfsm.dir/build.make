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
include CMakeFiles/smfsm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/smfsm.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/smfsm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/smfsm.dir/flags.make

CMakeFiles/smfsm.dir/src/smfsm/state.cpp.o: CMakeFiles/smfsm.dir/flags.make
CMakeFiles/smfsm.dir/src/smfsm/state.cpp.o: /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/state.cpp
CMakeFiles/smfsm.dir/src/smfsm/state.cpp.o: CMakeFiles/smfsm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robodog/RoboDog/ros2_ws/build/motion_cmd/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/smfsm.dir/src/smfsm/state.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/smfsm.dir/src/smfsm/state.cpp.o -MF CMakeFiles/smfsm.dir/src/smfsm/state.cpp.o.d -o CMakeFiles/smfsm.dir/src/smfsm/state.cpp.o -c /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/state.cpp

CMakeFiles/smfsm.dir/src/smfsm/state.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smfsm.dir/src/smfsm/state.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/state.cpp > CMakeFiles/smfsm.dir/src/smfsm/state.cpp.i

CMakeFiles/smfsm.dir/src/smfsm/state.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smfsm.dir/src/smfsm/state.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/state.cpp -o CMakeFiles/smfsm.dir/src/smfsm/state.cpp.s

CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.o: CMakeFiles/smfsm.dir/flags.make
CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.o: /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/idle.cpp
CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.o: CMakeFiles/smfsm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robodog/RoboDog/ros2_ws/build/motion_cmd/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.o -MF CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.o.d -o CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.o -c /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/idle.cpp

CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/idle.cpp > CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.i

CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/idle.cpp -o CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.s

CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.o: CMakeFiles/smfsm.dir/flags.make
CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.o: /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/stand.cpp
CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.o: CMakeFiles/smfsm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robodog/RoboDog/ros2_ws/build/motion_cmd/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.o -MF CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.o.d -o CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.o -c /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/stand.cpp

CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/stand.cpp > CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.i

CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/stand.cpp -o CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.s

CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.o: CMakeFiles/smfsm.dir/flags.make
CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.o: /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/transition_stand.cpp
CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.o: CMakeFiles/smfsm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robodog/RoboDog/ros2_ws/build/motion_cmd/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.o -MF CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.o.d -o CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.o -c /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/transition_stand.cpp

CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/transition_stand.cpp > CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.i

CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/transition_stand.cpp -o CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.s

CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.o: CMakeFiles/smfsm.dir/flags.make
CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.o: /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/transition_idle.cpp
CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.o: CMakeFiles/smfsm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robodog/RoboDog/ros2_ws/build/motion_cmd/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.o -MF CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.o.d -o CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.o -c /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/transition_idle.cpp

CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/transition_idle.cpp > CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.i

CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/transition_idle.cpp -o CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.s

CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.o: CMakeFiles/smfsm.dir/flags.make
CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.o: /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/walk.cpp
CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.o: CMakeFiles/smfsm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robodog/RoboDog/ros2_ws/build/motion_cmd/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.o -MF CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.o.d -o CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.o -c /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/walk.cpp

CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/walk.cpp > CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.i

CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robodog/RoboDog/ros2_ws/src/motion_cmd/src/smfsm/walk.cpp -o CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.s

# Object files for target smfsm
smfsm_OBJECTS = \
"CMakeFiles/smfsm.dir/src/smfsm/state.cpp.o" \
"CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.o" \
"CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.o" \
"CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.o" \
"CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.o" \
"CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.o"

# External object files for target smfsm
smfsm_EXTERNAL_OBJECTS =

libsmfsm.a: CMakeFiles/smfsm.dir/src/smfsm/state.cpp.o
libsmfsm.a: CMakeFiles/smfsm.dir/src/smfsm/idle.cpp.o
libsmfsm.a: CMakeFiles/smfsm.dir/src/smfsm/stand.cpp.o
libsmfsm.a: CMakeFiles/smfsm.dir/src/smfsm/transition_stand.cpp.o
libsmfsm.a: CMakeFiles/smfsm.dir/src/smfsm/transition_idle.cpp.o
libsmfsm.a: CMakeFiles/smfsm.dir/src/smfsm/walk.cpp.o
libsmfsm.a: CMakeFiles/smfsm.dir/build.make
libsmfsm.a: CMakeFiles/smfsm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robodog/RoboDog/ros2_ws/build/motion_cmd/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libsmfsm.a"
	$(CMAKE_COMMAND) -P CMakeFiles/smfsm.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/smfsm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/smfsm.dir/build: libsmfsm.a
.PHONY : CMakeFiles/smfsm.dir/build

CMakeFiles/smfsm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/smfsm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/smfsm.dir/clean

CMakeFiles/smfsm.dir/depend:
	cd /home/robodog/RoboDog/ros2_ws/build/motion_cmd && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robodog/RoboDog/ros2_ws/src/motion_cmd /home/robodog/RoboDog/ros2_ws/src/motion_cmd /home/robodog/RoboDog/ros2_ws/build/motion_cmd /home/robodog/RoboDog/ros2_ws/build/motion_cmd /home/robodog/RoboDog/ros2_ws/build/motion_cmd/CMakeFiles/smfsm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/smfsm.dir/depend
