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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wigwam/dev/sp18/mp/1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wigwam/dev/sp18/mp/1

# Include any dependencies generated for this target.
include CMakeFiles/sat.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sat.dir/flags.make

CMakeFiles/sat.dir/sat.cpp.o: CMakeFiles/sat.dir/flags.make
CMakeFiles/sat.dir/sat.cpp.o: sat.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wigwam/dev/sp18/mp/1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sat.dir/sat.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sat.dir/sat.cpp.o -c /Users/wigwam/dev/sp18/mp/1/sat.cpp

CMakeFiles/sat.dir/sat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sat.dir/sat.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wigwam/dev/sp18/mp/1/sat.cpp > CMakeFiles/sat.dir/sat.cpp.i

CMakeFiles/sat.dir/sat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sat.dir/sat.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wigwam/dev/sp18/mp/1/sat.cpp -o CMakeFiles/sat.dir/sat.cpp.s

CMakeFiles/sat.dir/sat.cpp.o.requires:

.PHONY : CMakeFiles/sat.dir/sat.cpp.o.requires

CMakeFiles/sat.dir/sat.cpp.o.provides: CMakeFiles/sat.dir/sat.cpp.o.requires
	$(MAKE) -f CMakeFiles/sat.dir/build.make CMakeFiles/sat.dir/sat.cpp.o.provides.build
.PHONY : CMakeFiles/sat.dir/sat.cpp.o.provides

CMakeFiles/sat.dir/sat.cpp.o.provides.build: CMakeFiles/sat.dir/sat.cpp.o


# Object files for target sat
sat_OBJECTS = \
"CMakeFiles/sat.dir/sat.cpp.o"

# External object files for target sat
sat_EXTERNAL_OBJECTS =

sat: CMakeFiles/sat.dir/sat.cpp.o
sat: CMakeFiles/sat.dir/build.make
sat: /usr/local/lib/libvtkm_cont-1.0.1.dylib
sat: CMakeFiles/sat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wigwam/dev/sp18/mp/1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sat"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sat.dir/build: sat

.PHONY : CMakeFiles/sat.dir/build

CMakeFiles/sat.dir/requires: CMakeFiles/sat.dir/sat.cpp.o.requires

.PHONY : CMakeFiles/sat.dir/requires

CMakeFiles/sat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sat.dir/clean

CMakeFiles/sat.dir/depend:
	cd /Users/wigwam/dev/sp18/mp/1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wigwam/dev/sp18/mp/1 /Users/wigwam/dev/sp18/mp/1 /Users/wigwam/dev/sp18/mp/1 /Users/wigwam/dev/sp18/mp/1 /Users/wigwam/dev/sp18/mp/1/CMakeFiles/sat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sat.dir/depend

