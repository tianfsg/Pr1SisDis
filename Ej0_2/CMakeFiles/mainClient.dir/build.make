# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/ubuntu/comp/Ej0_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/comp/Ej0_2

# Include any dependencies generated for this target.
include CMakeFiles/mainClient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mainClient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mainClient.dir/flags.make

CMakeFiles/mainClient.dir/main.cpp.o: CMakeFiles/mainClient.dir/flags.make
CMakeFiles/mainClient.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/comp/Ej0_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mainClient.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mainClient.dir/main.cpp.o -c /home/ubuntu/comp/Ej0_2/main.cpp

CMakeFiles/mainClient.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mainClient.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/comp/Ej0_2/main.cpp > CMakeFiles/mainClient.dir/main.cpp.i

CMakeFiles/mainClient.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mainClient.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/comp/Ej0_2/main.cpp -o CMakeFiles/mainClient.dir/main.cpp.s

CMakeFiles/mainClient.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/mainClient.dir/main.cpp.o.requires

CMakeFiles/mainClient.dir/main.cpp.o.provides: CMakeFiles/mainClient.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/mainClient.dir/build.make CMakeFiles/mainClient.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/mainClient.dir/main.cpp.o.provides

CMakeFiles/mainClient.dir/main.cpp.o.provides.build: CMakeFiles/mainClient.dir/main.cpp.o


CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o: CMakeFiles/mainClient.dir/flags.make
CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o: holaMundo_stub.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/comp/Ej0_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o -c /home/ubuntu/comp/Ej0_2/holaMundo_stub.cpp

CMakeFiles/mainClient.dir/holaMundo_stub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mainClient.dir/holaMundo_stub.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/comp/Ej0_2/holaMundo_stub.cpp > CMakeFiles/mainClient.dir/holaMundo_stub.cpp.i

CMakeFiles/mainClient.dir/holaMundo_stub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mainClient.dir/holaMundo_stub.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/comp/Ej0_2/holaMundo_stub.cpp -o CMakeFiles/mainClient.dir/holaMundo_stub.cpp.s

CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o.requires:

.PHONY : CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o.requires

CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o.provides: CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o.requires
	$(MAKE) -f CMakeFiles/mainClient.dir/build.make CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o.provides.build
.PHONY : CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o.provides

CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o.provides.build: CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o


CMakeFiles/mainClient.dir/utils.cpp.o: CMakeFiles/mainClient.dir/flags.make
CMakeFiles/mainClient.dir/utils.cpp.o: utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/comp/Ej0_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mainClient.dir/utils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mainClient.dir/utils.cpp.o -c /home/ubuntu/comp/Ej0_2/utils.cpp

CMakeFiles/mainClient.dir/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mainClient.dir/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/comp/Ej0_2/utils.cpp > CMakeFiles/mainClient.dir/utils.cpp.i

CMakeFiles/mainClient.dir/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mainClient.dir/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/comp/Ej0_2/utils.cpp -o CMakeFiles/mainClient.dir/utils.cpp.s

CMakeFiles/mainClient.dir/utils.cpp.o.requires:

.PHONY : CMakeFiles/mainClient.dir/utils.cpp.o.requires

CMakeFiles/mainClient.dir/utils.cpp.o.provides: CMakeFiles/mainClient.dir/utils.cpp.o.requires
	$(MAKE) -f CMakeFiles/mainClient.dir/build.make CMakeFiles/mainClient.dir/utils.cpp.o.provides.build
.PHONY : CMakeFiles/mainClient.dir/utils.cpp.o.provides

CMakeFiles/mainClient.dir/utils.cpp.o.provides.build: CMakeFiles/mainClient.dir/utils.cpp.o


# Object files for target mainClient
mainClient_OBJECTS = \
"CMakeFiles/mainClient.dir/main.cpp.o" \
"CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o" \
"CMakeFiles/mainClient.dir/utils.cpp.o"

# External object files for target mainClient
mainClient_EXTERNAL_OBJECTS =

mainClient: CMakeFiles/mainClient.dir/main.cpp.o
mainClient: CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o
mainClient: CMakeFiles/mainClient.dir/utils.cpp.o
mainClient: CMakeFiles/mainClient.dir/build.make
mainClient: CMakeFiles/mainClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/comp/Ej0_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable mainClient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mainClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mainClient.dir/build: mainClient

.PHONY : CMakeFiles/mainClient.dir/build

CMakeFiles/mainClient.dir/requires: CMakeFiles/mainClient.dir/main.cpp.o.requires
CMakeFiles/mainClient.dir/requires: CMakeFiles/mainClient.dir/holaMundo_stub.cpp.o.requires
CMakeFiles/mainClient.dir/requires: CMakeFiles/mainClient.dir/utils.cpp.o.requires

.PHONY : CMakeFiles/mainClient.dir/requires

CMakeFiles/mainClient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mainClient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mainClient.dir/clean

CMakeFiles/mainClient.dir/depend:
	cd /home/ubuntu/comp/Ej0_2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/comp/Ej0_2 /home/ubuntu/comp/Ej0_2 /home/ubuntu/comp/Ej0_2 /home/ubuntu/comp/Ej0_2 /home/ubuntu/comp/Ej0_2/CMakeFiles/mainClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mainClient.dir/depend

