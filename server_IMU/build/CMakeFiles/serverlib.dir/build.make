# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stashako/cpp_test/Pipe_Crawler_IMU_simulation/server_IMU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stashako/cpp_test/Pipe_Crawler_IMU_simulation/server_IMU/build

# Include any dependencies generated for this target.
include CMakeFiles/serverlib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/serverlib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/serverlib.dir/flags.make

CMakeFiles/serverlib.dir/lib/IMU_server.cpp.o: CMakeFiles/serverlib.dir/flags.make
CMakeFiles/serverlib.dir/lib/IMU_server.cpp.o: ../lib/IMU_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stashako/cpp_test/Pipe_Crawler_IMU_simulation/server_IMU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/serverlib.dir/lib/IMU_server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serverlib.dir/lib/IMU_server.cpp.o -c /home/stashako/cpp_test/Pipe_Crawler_IMU_simulation/server_IMU/lib/IMU_server.cpp

CMakeFiles/serverlib.dir/lib/IMU_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serverlib.dir/lib/IMU_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stashako/cpp_test/Pipe_Crawler_IMU_simulation/server_IMU/lib/IMU_server.cpp > CMakeFiles/serverlib.dir/lib/IMU_server.cpp.i

CMakeFiles/serverlib.dir/lib/IMU_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serverlib.dir/lib/IMU_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stashako/cpp_test/Pipe_Crawler_IMU_simulation/server_IMU/lib/IMU_server.cpp -o CMakeFiles/serverlib.dir/lib/IMU_server.cpp.s

# Object files for target serverlib
serverlib_OBJECTS = \
"CMakeFiles/serverlib.dir/lib/IMU_server.cpp.o"

# External object files for target serverlib
serverlib_EXTERNAL_OBJECTS =

libserverlib.a: CMakeFiles/serverlib.dir/lib/IMU_server.cpp.o
libserverlib.a: CMakeFiles/serverlib.dir/build.make
libserverlib.a: CMakeFiles/serverlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stashako/cpp_test/Pipe_Crawler_IMU_simulation/server_IMU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libserverlib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/serverlib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serverlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/serverlib.dir/build: libserverlib.a

.PHONY : CMakeFiles/serverlib.dir/build

CMakeFiles/serverlib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/serverlib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/serverlib.dir/clean

CMakeFiles/serverlib.dir/depend:
	cd /home/stashako/cpp_test/Pipe_Crawler_IMU_simulation/server_IMU/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stashako/cpp_test/Pipe_Crawler_IMU_simulation/server_IMU /home/stashako/cpp_test/Pipe_Crawler_IMU_simulation/server_IMU /home/stashako/cpp_test/Pipe_Crawler_IMU_simulation/server_IMU/build /home/stashako/cpp_test/Pipe_Crawler_IMU_simulation/server_IMU/build /home/stashako/cpp_test/Pipe_Crawler_IMU_simulation/server_IMU/build/CMakeFiles/serverlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/serverlib.dir/depend

