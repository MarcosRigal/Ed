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
CMAKE_SOURCE_DIR = /home/marcos/Repositories/University/Ed/P3/i92rigam/avl-tree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcos/Repositories/University/Ed/P3/i92rigam/build-avl-tree-Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/test_bstree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_bstree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_bstree.dir/flags.make

CMakeFiles/test_bstree.dir/test_avltree.cpp.o: CMakeFiles/test_bstree.dir/flags.make
CMakeFiles/test_bstree.dir/test_avltree.cpp.o: /home/marcos/Repositories/University/Ed/P3/i92rigam/avl-tree/test_avltree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/Repositories/University/Ed/P3/i92rigam/build-avl-tree-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_bstree.dir/test_avltree.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_bstree.dir/test_avltree.cpp.o -c /home/marcos/Repositories/University/Ed/P3/i92rigam/avl-tree/test_avltree.cpp

CMakeFiles/test_bstree.dir/test_avltree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_bstree.dir/test_avltree.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcos/Repositories/University/Ed/P3/i92rigam/avl-tree/test_avltree.cpp > CMakeFiles/test_bstree.dir/test_avltree.cpp.i

CMakeFiles/test_bstree.dir/test_avltree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_bstree.dir/test_avltree.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcos/Repositories/University/Ed/P3/i92rigam/avl-tree/test_avltree.cpp -o CMakeFiles/test_bstree.dir/test_avltree.cpp.s

# Object files for target test_bstree
test_bstree_OBJECTS = \
"CMakeFiles/test_bstree.dir/test_avltree.cpp.o"

# External object files for target test_bstree
test_bstree_EXTERNAL_OBJECTS =

test_bstree: CMakeFiles/test_bstree.dir/test_avltree.cpp.o
test_bstree: CMakeFiles/test_bstree.dir/build.make
test_bstree: CMakeFiles/test_bstree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcos/Repositories/University/Ed/P3/i92rigam/build-avl-tree-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_bstree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_bstree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_bstree.dir/build: test_bstree

.PHONY : CMakeFiles/test_bstree.dir/build

CMakeFiles/test_bstree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_bstree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_bstree.dir/clean

CMakeFiles/test_bstree.dir/depend:
	cd /home/marcos/Repositories/University/Ed/P3/i92rigam/build-avl-tree-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcos/Repositories/University/Ed/P3/i92rigam/avl-tree /home/marcos/Repositories/University/Ed/P3/i92rigam/avl-tree /home/marcos/Repositories/University/Ed/P3/i92rigam/build-avl-tree-Desktop-Debug /home/marcos/Repositories/University/Ed/P3/i92rigam/build-avl-tree-Desktop-Debug /home/marcos/Repositories/University/Ed/P3/i92rigam/build-avl-tree-Desktop-Debug/CMakeFiles/test_bstree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_bstree.dir/depend

