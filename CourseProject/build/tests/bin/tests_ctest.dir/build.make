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
include tests/CMakeFiles/../../tests/bin/tests_ctest.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/../../tests/bin/tests_ctest.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/../../tests/bin/tests_ctest.dir/flags.make

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/flags.make
tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o: ../tests/src/main_ctest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Загрузки/CompArch-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o"
	cd /home/mark/Загрузки/CompArch-master/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o   -c /home/mark/Загрузки/CompArch-master/tests/src/main_ctest.c

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.i"
	cd /home/mark/Загрузки/CompArch-master/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mark/Загрузки/CompArch-master/tests/src/main_ctest.c > CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.i

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.s"
	cd /home/mark/Загрузки/CompArch-master/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mark/Загрузки/CompArch-master/tests/src/main_ctest.c -o CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.s

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o.requires:

.PHONY : tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o.requires

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o.provides: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o.requires
	$(MAKE) -f tests/CMakeFiles/../../tests/bin/tests_ctest.dir/build.make tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o.provides.build
.PHONY : tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o.provides

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o.provides.build: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o


tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/flags.make
tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o: ../tests/src/testsSC_ctest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Загрузки/CompArch-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o"
	cd /home/mark/Загрузки/CompArch-master/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o   -c /home/mark/Загрузки/CompArch-master/tests/src/testsSC_ctest.c

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.i"
	cd /home/mark/Загрузки/CompArch-master/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mark/Загрузки/CompArch-master/tests/src/testsSC_ctest.c > CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.i

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.s"
	cd /home/mark/Загрузки/CompArch-master/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mark/Загрузки/CompArch-master/tests/src/testsSC_ctest.c -o CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.s

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o.requires:

.PHONY : tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o.requires

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o.provides: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o.requires
	$(MAKE) -f tests/CMakeFiles/../../tests/bin/tests_ctest.dir/build.make tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o.provides.build
.PHONY : tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o.provides

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o.provides.build: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o


tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/flags.make
tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o: ../tests/src/testsAsm_ctest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Загрузки/CompArch-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o"
	cd /home/mark/Загрузки/CompArch-master/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o   -c /home/mark/Загрузки/CompArch-master/tests/src/testsAsm_ctest.c

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.i"
	cd /home/mark/Загрузки/CompArch-master/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mark/Загрузки/CompArch-master/tests/src/testsAsm_ctest.c > CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.i

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.s"
	cd /home/mark/Загрузки/CompArch-master/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mark/Загрузки/CompArch-master/tests/src/testsAsm_ctest.c -o CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.s

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o.requires:

.PHONY : tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o.requires

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o.provides: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o.requires
	$(MAKE) -f tests/CMakeFiles/../../tests/bin/tests_ctest.dir/build.make tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o.provides.build
.PHONY : tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o.provides

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o.provides.build: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o


tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/flags.make
tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o: ../tests/src/testsBasic_ctest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Загрузки/CompArch-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o"
	cd /home/mark/Загрузки/CompArch-master/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o   -c /home/mark/Загрузки/CompArch-master/tests/src/testsBasic_ctest.c

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.i"
	cd /home/mark/Загрузки/CompArch-master/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mark/Загрузки/CompArch-master/tests/src/testsBasic_ctest.c > CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.i

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.s"
	cd /home/mark/Загрузки/CompArch-master/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mark/Загрузки/CompArch-master/tests/src/testsBasic_ctest.c -o CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.s

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o.requires:

.PHONY : tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o.requires

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o.provides: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o.requires
	$(MAKE) -f tests/CMakeFiles/../../tests/bin/tests_ctest.dir/build.make tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o.provides.build
.PHONY : tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o.provides

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o.provides.build: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o


# Object files for target ../../tests/bin/tests_ctest
__/__/tests/bin/tests_ctest_OBJECTS = \
"CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o" \
"CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o" \
"CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o" \
"CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o"

# External object files for target ../../tests/bin/tests_ctest
__/__/tests/bin/tests_ctest_EXTERNAL_OBJECTS =

tests/../../tests/bin/tests_ctest: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o
tests/../../tests/bin/tests_ctest: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o
tests/../../tests/bin/tests_ctest: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o
tests/../../tests/bin/tests_ctest: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o
tests/../../tests/bin/tests_ctest: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/build.make
tests/../../tests/bin/tests_ctest: basic/libBasic.a
tests/../../tests/bin/tests_ctest: asm/libAsm.a
tests/../../tests/bin/tests_ctest: cpu/libCPU.a
tests/../../tests/bin/tests_ctest: consoleSC/libTerm.a
tests/../../tests/bin/tests_ctest: simpleComputer/libSimpleComputer.a
tests/../../tests/bin/tests_ctest: print/libWrite.a
tests/../../tests/bin/tests_ctest: scan/libReadInt.a
tests/../../tests/bin/tests_ctest: bc/libBigChars.a
tests/../../tests/bin/tests_ctest: readKey/libReadKey.a
tests/../../tests/bin/tests_ctest: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/Загрузки/CompArch-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable ../../tests/bin/tests_ctest"
	cd /home/mark/Загрузки/CompArch-master/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/../../tests/bin/tests_ctest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/../../tests/bin/tests_ctest.dir/build: tests/../../tests/bin/tests_ctest

.PHONY : tests/CMakeFiles/../../tests/bin/tests_ctest.dir/build

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/requires: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/main_ctest.c.o.requires
tests/CMakeFiles/../../tests/bin/tests_ctest.dir/requires: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsSC_ctest.c.o.requires
tests/CMakeFiles/../../tests/bin/tests_ctest.dir/requires: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsAsm_ctest.c.o.requires
tests/CMakeFiles/../../tests/bin/tests_ctest.dir/requires: tests/CMakeFiles/../../tests/bin/tests_ctest.dir/src/testsBasic_ctest.c.o.requires

.PHONY : tests/CMakeFiles/../../tests/bin/tests_ctest.dir/requires

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/clean:
	cd /home/mark/Загрузки/CompArch-master/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/../../tests/bin/tests_ctest.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/../../tests/bin/tests_ctest.dir/clean

tests/CMakeFiles/../../tests/bin/tests_ctest.dir/depend:
	cd /home/mark/Загрузки/CompArch-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/Загрузки/CompArch-master /home/mark/Загрузки/CompArch-master/tests /home/mark/Загрузки/CompArch-master/build /home/mark/Загрузки/CompArch-master/build/tests /home/mark/Загрузки/CompArch-master/build/tests/bin/tests_ctest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/../../tests/bin/tests_ctest.dir/depend
