# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/mark/Загрузки/CompArch-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mark/Загрузки/CompArch-master/build

# Include any dependencies generated for this target.
include scan/CMakeFiles/ReadInt.dir/depend.make

# Include the progress variables for this target.
include scan/CMakeFiles/ReadInt.dir/progress.make

# Include the compile flags for this target's objects.
include scan/CMakeFiles/ReadInt.dir/flags.make

scan/CMakeFiles/ReadInt.dir/src/readInt.c.o: scan/CMakeFiles/ReadInt.dir/flags.make
scan/CMakeFiles/ReadInt.dir/src/readInt.c.o: ../scan/src/readInt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Загрузки/CompArch-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object scan/CMakeFiles/ReadInt.dir/src/readInt.c.o"
	cd /home/mark/Загрузки/CompArch-master/build/scan && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ReadInt.dir/src/readInt.c.o   -c /home/mark/Загрузки/CompArch-master/scan/src/readInt.c

scan/CMakeFiles/ReadInt.dir/src/readInt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ReadInt.dir/src/readInt.c.i"
	cd /home/mark/Загрузки/CompArch-master/build/scan && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mark/Загрузки/CompArch-master/scan/src/readInt.c > CMakeFiles/ReadInt.dir/src/readInt.c.i

scan/CMakeFiles/ReadInt.dir/src/readInt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ReadInt.dir/src/readInt.c.s"
	cd /home/mark/Загрузки/CompArch-master/build/scan && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mark/Загрузки/CompArch-master/scan/src/readInt.c -o CMakeFiles/ReadInt.dir/src/readInt.c.s

scan/CMakeFiles/ReadInt.dir/src/readInt.c.o.requires:

.PHONY : scan/CMakeFiles/ReadInt.dir/src/readInt.c.o.requires

scan/CMakeFiles/ReadInt.dir/src/readInt.c.o.provides: scan/CMakeFiles/ReadInt.dir/src/readInt.c.o.requires
	$(MAKE) -f scan/CMakeFiles/ReadInt.dir/build.make scan/CMakeFiles/ReadInt.dir/src/readInt.c.o.provides.build
.PHONY : scan/CMakeFiles/ReadInt.dir/src/readInt.c.o.provides

scan/CMakeFiles/ReadInt.dir/src/readInt.c.o.provides.build: scan/CMakeFiles/ReadInt.dir/src/readInt.c.o


# Object files for target ReadInt
ReadInt_OBJECTS = \
"CMakeFiles/ReadInt.dir/src/readInt.c.o"

# External object files for target ReadInt
ReadInt_EXTERNAL_OBJECTS =

scan/libReadInt.a: scan/CMakeFiles/ReadInt.dir/src/readInt.c.o
scan/libReadInt.a: scan/CMakeFiles/ReadInt.dir/build.make
scan/libReadInt.a: scan/CMakeFiles/ReadInt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/Загрузки/CompArch-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libReadInt.a"
	cd /home/mark/Загрузки/CompArch-master/build/scan && $(CMAKE_COMMAND) -P CMakeFiles/ReadInt.dir/cmake_clean_target.cmake
	cd /home/mark/Загрузки/CompArch-master/build/scan && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ReadInt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
scan/CMakeFiles/ReadInt.dir/build: scan/libReadInt.a

.PHONY : scan/CMakeFiles/ReadInt.dir/build

scan/CMakeFiles/ReadInt.dir/requires: scan/CMakeFiles/ReadInt.dir/src/readInt.c.o.requires

.PHONY : scan/CMakeFiles/ReadInt.dir/requires

scan/CMakeFiles/ReadInt.dir/clean:
	cd /home/mark/Загрузки/CompArch-master/build/scan && $(CMAKE_COMMAND) -P CMakeFiles/ReadInt.dir/cmake_clean.cmake
.PHONY : scan/CMakeFiles/ReadInt.dir/clean

scan/CMakeFiles/ReadInt.dir/depend:
	cd /home/mark/Загрузки/CompArch-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/Загрузки/CompArch-master /home/mark/Загрузки/CompArch-master/scan /home/mark/Загрузки/CompArch-master/build /home/mark/Загрузки/CompArch-master/build/scan /home/mark/Загрузки/CompArch-master/build/scan/CMakeFiles/ReadInt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : scan/CMakeFiles/ReadInt.dir/depend
