# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/yiting/Downloads/clion-2019.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/yiting/Downloads/clion-2019.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project.dir/flags.make

CMakeFiles/project.dir/main.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/main.cpp.o -c /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/main.cpp

CMakeFiles/project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/main.cpp > CMakeFiles/project.dir/main.cpp.i

CMakeFiles/project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/main.cpp -o CMakeFiles/project.dir/main.cpp.s

CMakeFiles/project.dir/src/Matrix.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/src/Matrix.cpp.o: ../src/Matrix.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/project.dir/src/Matrix.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/src/Matrix.cpp.o -c /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/src/Matrix.cpp

CMakeFiles/project.dir/src/Matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/src/Matrix.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/src/Matrix.cpp > CMakeFiles/project.dir/src/Matrix.cpp.i

CMakeFiles/project.dir/src/Matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/src/Matrix.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/src/Matrix.cpp -o CMakeFiles/project.dir/src/Matrix.cpp.s

CMakeFiles/project.dir/src/Fitter.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/src/Fitter.cpp.o: ../src/Fitter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/project.dir/src/Fitter.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/src/Fitter.cpp.o -c /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/src/Fitter.cpp

CMakeFiles/project.dir/src/Fitter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/src/Fitter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/src/Fitter.cpp > CMakeFiles/project.dir/src/Fitter.cpp.i

CMakeFiles/project.dir/src/Fitter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/src/Fitter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/src/Fitter.cpp -o CMakeFiles/project.dir/src/Fitter.cpp.s

CMakeFiles/project.dir/test/DataIO.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/test/DataIO.cpp.o: ../test/DataIO.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/project.dir/test/DataIO.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/test/DataIO.cpp.o -c /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/test/DataIO.cpp

CMakeFiles/project.dir/test/DataIO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/test/DataIO.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/test/DataIO.cpp > CMakeFiles/project.dir/test/DataIO.cpp.i

CMakeFiles/project.dir/test/DataIO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/test/DataIO.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/test/DataIO.cpp -o CMakeFiles/project.dir/test/DataIO.cpp.s

CMakeFiles/project.dir/test/gnuplot_i.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/test/gnuplot_i.cpp.o: ../test/gnuplot_i.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/project.dir/test/gnuplot_i.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/test/gnuplot_i.cpp.o -c /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/test/gnuplot_i.cpp

CMakeFiles/project.dir/test/gnuplot_i.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/test/gnuplot_i.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/test/gnuplot_i.cpp > CMakeFiles/project.dir/test/gnuplot_i.cpp.i

CMakeFiles/project.dir/test/gnuplot_i.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/test/gnuplot_i.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/test/gnuplot_i.cpp -o CMakeFiles/project.dir/test/gnuplot_i.cpp.s

CMakeFiles/project.dir/test/Config.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/test/Config.cpp.o: ../test/Config.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/project.dir/test/Config.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/test/Config.cpp.o -c /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/test/Config.cpp

CMakeFiles/project.dir/test/Config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/test/Config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/test/Config.cpp > CMakeFiles/project.dir/test/Config.cpp.i

CMakeFiles/project.dir/test/Config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/test/Config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/test/Config.cpp -o CMakeFiles/project.dir/test/Config.cpp.s

CMakeFiles/project.dir/test/Test.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/test/Test.cpp.o: ../test/Test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/project.dir/test/Test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/test/Test.cpp.o -c /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/test/Test.cpp

CMakeFiles/project.dir/test/Test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/test/Test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/test/Test.cpp > CMakeFiles/project.dir/test/Test.cpp.i

CMakeFiles/project.dir/test/Test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/test/Test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/test/Test.cpp -o CMakeFiles/project.dir/test/Test.cpp.s

# Object files for target project
project_OBJECTS = \
"CMakeFiles/project.dir/main.cpp.o" \
"CMakeFiles/project.dir/src/Matrix.cpp.o" \
"CMakeFiles/project.dir/src/Fitter.cpp.o" \
"CMakeFiles/project.dir/test/DataIO.cpp.o" \
"CMakeFiles/project.dir/test/gnuplot_i.cpp.o" \
"CMakeFiles/project.dir/test/Config.cpp.o" \
"CMakeFiles/project.dir/test/Test.cpp.o"

# External object files for target project
project_EXTERNAL_OBJECTS =

project: CMakeFiles/project.dir/main.cpp.o
project: CMakeFiles/project.dir/src/Matrix.cpp.o
project: CMakeFiles/project.dir/src/Fitter.cpp.o
project: CMakeFiles/project.dir/test/DataIO.cpp.o
project: CMakeFiles/project.dir/test/gnuplot_i.cpp.o
project: CMakeFiles/project.dir/test/Config.cpp.o
project: CMakeFiles/project.dir/test/Test.cpp.o
project: CMakeFiles/project.dir/build.make
project: CMakeFiles/project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project.dir/build: project

.PHONY : CMakeFiles/project.dir/build

CMakeFiles/project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project.dir/clean

CMakeFiles/project.dir/depend:
	cd /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/cmake-build-debug /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/cmake-build-debug /home/yiting/Documents/yiting/PCSC_project/PCSC_2019_Data_Approx/cmake-build-debug/CMakeFiles/project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project.dir/depend

