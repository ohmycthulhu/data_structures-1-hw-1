# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/clion/169/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/169/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cthulhu/CLionProjects/PW1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cthulhu/CLionProjects/PW1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PW1.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/PW1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PW1.dir/flags.make

CMakeFiles/PW1.dir/normal.c.o: CMakeFiles/PW1.dir/flags.make
CMakeFiles/PW1.dir/normal.c.o: ../normal.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cthulhu/CLionProjects/PW1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/PW1.dir/normal.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PW1.dir/normal.c.o -c /home/cthulhu/CLionProjects/PW1/normal.c

CMakeFiles/PW1.dir/normal.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PW1.dir/normal.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cthulhu/CLionProjects/PW1/normal.c > CMakeFiles/PW1.dir/normal.c.i

CMakeFiles/PW1.dir/normal.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PW1.dir/normal.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cthulhu/CLionProjects/PW1/normal.c -o CMakeFiles/PW1.dir/normal.c.s

# Object files for target PW1
PW1_OBJECTS = \
"CMakeFiles/PW1.dir/normal.c.o"

# External object files for target PW1
PW1_EXTERNAL_OBJECTS =

PW1: CMakeFiles/PW1.dir/normal.c.o
PW1: CMakeFiles/PW1.dir/build.make
PW1: CMakeFiles/PW1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cthulhu/CLionProjects/PW1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable PW1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PW1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PW1.dir/build: PW1
.PHONY : CMakeFiles/PW1.dir/build

CMakeFiles/PW1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PW1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PW1.dir/clean

CMakeFiles/PW1.dir/depend:
	cd /home/cthulhu/CLionProjects/PW1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cthulhu/CLionProjects/PW1 /home/cthulhu/CLionProjects/PW1 /home/cthulhu/CLionProjects/PW1/cmake-build-debug /home/cthulhu/CLionProjects/PW1/cmake-build-debug /home/cthulhu/CLionProjects/PW1/cmake-build-debug/CMakeFiles/PW1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PW1.dir/depend
