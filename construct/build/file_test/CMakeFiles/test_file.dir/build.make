# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /workspace/github/cCode/cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspace/github/cCode/cmake/build

# Include any dependencies generated for this target.
include file_test/CMakeFiles/test_file.dir/depend.make

# Include the progress variables for this target.
include file_test/CMakeFiles/test_file.dir/progress.make

# Include the compile flags for this target's objects.
include file_test/CMakeFiles/test_file.dir/flags.make

file_test/CMakeFiles/test_file.dir/test_file.c.o: file_test/CMakeFiles/test_file.dir/flags.make
file_test/CMakeFiles/test_file.dir/test_file.c.o: ../file_test/test_file.c
	$(CMAKE_COMMAND) -E cmake_progress_report /workspace/github/cCode/cmake/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object file_test/CMakeFiles/test_file.dir/test_file.c.o"
	cd /workspace/github/cCode/cmake/build/file_test && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_file.dir/test_file.c.o   -c /workspace/github/cCode/cmake/file_test/test_file.c

file_test/CMakeFiles/test_file.dir/test_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_file.dir/test_file.c.i"
	cd /workspace/github/cCode/cmake/build/file_test && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /workspace/github/cCode/cmake/file_test/test_file.c > CMakeFiles/test_file.dir/test_file.c.i

file_test/CMakeFiles/test_file.dir/test_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_file.dir/test_file.c.s"
	cd /workspace/github/cCode/cmake/build/file_test && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /workspace/github/cCode/cmake/file_test/test_file.c -o CMakeFiles/test_file.dir/test_file.c.s

file_test/CMakeFiles/test_file.dir/test_file.c.o.requires:
.PHONY : file_test/CMakeFiles/test_file.dir/test_file.c.o.requires

file_test/CMakeFiles/test_file.dir/test_file.c.o.provides: file_test/CMakeFiles/test_file.dir/test_file.c.o.requires
	$(MAKE) -f file_test/CMakeFiles/test_file.dir/build.make file_test/CMakeFiles/test_file.dir/test_file.c.o.provides.build
.PHONY : file_test/CMakeFiles/test_file.dir/test_file.c.o.provides

file_test/CMakeFiles/test_file.dir/test_file.c.o.provides.build: file_test/CMakeFiles/test_file.dir/test_file.c.o

# Object files for target test_file
test_file_OBJECTS = \
"CMakeFiles/test_file.dir/test_file.c.o"

# External object files for target test_file
test_file_EXTERNAL_OBJECTS =

file_test/libtest_file.a: file_test/CMakeFiles/test_file.dir/test_file.c.o
file_test/libtest_file.a: file_test/CMakeFiles/test_file.dir/build.make
file_test/libtest_file.a: file_test/CMakeFiles/test_file.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libtest_file.a"
	cd /workspace/github/cCode/cmake/build/file_test && $(CMAKE_COMMAND) -P CMakeFiles/test_file.dir/cmake_clean_target.cmake
	cd /workspace/github/cCode/cmake/build/file_test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_file.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
file_test/CMakeFiles/test_file.dir/build: file_test/libtest_file.a
.PHONY : file_test/CMakeFiles/test_file.dir/build

file_test/CMakeFiles/test_file.dir/requires: file_test/CMakeFiles/test_file.dir/test_file.c.o.requires
.PHONY : file_test/CMakeFiles/test_file.dir/requires

file_test/CMakeFiles/test_file.dir/clean:
	cd /workspace/github/cCode/cmake/build/file_test && $(CMAKE_COMMAND) -P CMakeFiles/test_file.dir/cmake_clean.cmake
.PHONY : file_test/CMakeFiles/test_file.dir/clean

file_test/CMakeFiles/test_file.dir/depend:
	cd /workspace/github/cCode/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspace/github/cCode/cmake /workspace/github/cCode/cmake/file_test /workspace/github/cCode/cmake/build /workspace/github/cCode/cmake/build/file_test /workspace/github/cCode/cmake/build/file_test/CMakeFiles/test_file.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : file_test/CMakeFiles/test_file.dir/depend

