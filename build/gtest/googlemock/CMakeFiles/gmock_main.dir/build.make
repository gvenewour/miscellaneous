# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/cmake-3.9.2/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake-3.9.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/travis/build/gvenewour/miscellaneous

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/travis/build/gvenewour/miscellaneous/build

# Include any dependencies generated for this target.
include gtest/googlemock/CMakeFiles/gmock_main.dir/depend.make

# Include the progress variables for this target.
include gtest/googlemock/CMakeFiles/gmock_main.dir/progress.make

# Include the compile flags for this target's objects.
include gtest/googlemock/CMakeFiles/gmock_main.dir/flags.make

gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o: gtest/googlemock/CMakeFiles/gmock_main.dir/flags.make
gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o: ../gtest/googlemock/src/gmock_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/travis/build/gvenewour/miscellaneous/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o"
	cd /home/travis/build/gvenewour/miscellaneous/build/gtest/googlemock && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gmock_main.dir/src/gmock_main.cc.o -c /home/travis/build/gvenewour/miscellaneous/gtest/googlemock/src/gmock_main.cc

gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock_main.dir/src/gmock_main.cc.i"
	cd /home/travis/build/gvenewour/miscellaneous/build/gtest/googlemock && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/travis/build/gvenewour/miscellaneous/gtest/googlemock/src/gmock_main.cc > CMakeFiles/gmock_main.dir/src/gmock_main.cc.i

gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock_main.dir/src/gmock_main.cc.s"
	cd /home/travis/build/gvenewour/miscellaneous/build/gtest/googlemock && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/travis/build/gvenewour/miscellaneous/gtest/googlemock/src/gmock_main.cc -o CMakeFiles/gmock_main.dir/src/gmock_main.cc.s

gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires:

.PHONY : gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires

gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides: gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires
	$(MAKE) -f gtest/googlemock/CMakeFiles/gmock_main.dir/build.make gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides.build
.PHONY : gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides

gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides.build: gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o


# Object files for target gmock_main
gmock_main_OBJECTS = \
"CMakeFiles/gmock_main.dir/src/gmock_main.cc.o"

# External object files for target gmock_main
gmock_main_EXTERNAL_OBJECTS =

gtest/googlemock/libgmock_main.a: gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
gtest/googlemock/libgmock_main.a: gtest/googlemock/CMakeFiles/gmock_main.dir/build.make
gtest/googlemock/libgmock_main.a: gtest/googlemock/CMakeFiles/gmock_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/travis/build/gvenewour/miscellaneous/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgmock_main.a"
	cd /home/travis/build/gvenewour/miscellaneous/build/gtest/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock_main.dir/cmake_clean_target.cmake
	cd /home/travis/build/gvenewour/miscellaneous/build/gtest/googlemock && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gmock_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
gtest/googlemock/CMakeFiles/gmock_main.dir/build: gtest/googlemock/libgmock_main.a

.PHONY : gtest/googlemock/CMakeFiles/gmock_main.dir/build

gtest/googlemock/CMakeFiles/gmock_main.dir/requires: gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires

.PHONY : gtest/googlemock/CMakeFiles/gmock_main.dir/requires

gtest/googlemock/CMakeFiles/gmock_main.dir/clean:
	cd /home/travis/build/gvenewour/miscellaneous/build/gtest/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock_main.dir/cmake_clean.cmake
.PHONY : gtest/googlemock/CMakeFiles/gmock_main.dir/clean

gtest/googlemock/CMakeFiles/gmock_main.dir/depend:
	cd /home/travis/build/gvenewour/miscellaneous/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/travis/build/gvenewour/miscellaneous /home/travis/build/gvenewour/miscellaneous/gtest/googlemock /home/travis/build/gvenewour/miscellaneous/build /home/travis/build/gvenewour/miscellaneous/build/gtest/googlemock /home/travis/build/gvenewour/miscellaneous/build/gtest/googlemock/CMakeFiles/gmock_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : gtest/googlemock/CMakeFiles/gmock_main.dir/depend

