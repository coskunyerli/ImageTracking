# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/coskunyerli/CLionProjects/Visualization

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/coskunyerli/CLionProjects/Visualization/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Tracker.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Tracker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tracker.dir/flags.make

CMakeFiles/Tracker.dir/track.cpp.o: CMakeFiles/Tracker.dir/flags.make
CMakeFiles/Tracker.dir/track.cpp.o: ../track.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/coskunyerli/CLionProjects/Visualization/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Tracker.dir/track.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tracker.dir/track.cpp.o -c /Users/coskunyerli/CLionProjects/Visualization/track.cpp

CMakeFiles/Tracker.dir/track.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tracker.dir/track.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/coskunyerli/CLionProjects/Visualization/track.cpp > CMakeFiles/Tracker.dir/track.cpp.i

CMakeFiles/Tracker.dir/track.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tracker.dir/track.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/coskunyerli/CLionProjects/Visualization/track.cpp -o CMakeFiles/Tracker.dir/track.cpp.s

CMakeFiles/Tracker.dir/track.cpp.o.requires:

.PHONY : CMakeFiles/Tracker.dir/track.cpp.o.requires

CMakeFiles/Tracker.dir/track.cpp.o.provides: CMakeFiles/Tracker.dir/track.cpp.o.requires
	$(MAKE) -f CMakeFiles/Tracker.dir/build.make CMakeFiles/Tracker.dir/track.cpp.o.provides.build
.PHONY : CMakeFiles/Tracker.dir/track.cpp.o.provides

CMakeFiles/Tracker.dir/track.cpp.o.provides.build: CMakeFiles/Tracker.dir/track.cpp.o


# Object files for target Tracker
Tracker_OBJECTS = \
"CMakeFiles/Tracker.dir/track.cpp.o"

# External object files for target Tracker
Tracker_EXTERNAL_OBJECTS =

Tracker: CMakeFiles/Tracker.dir/track.cpp.o
Tracker: CMakeFiles/Tracker.dir/build.make
Tracker: /usr/local/lib/libopencv_stitching.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_superres.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_videostab.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_aruco.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_bgsegm.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_bioinspired.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_ccalib.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_dpm.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_fuzzy.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_hdf.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_line_descriptor.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_optflow.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_reg.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_saliency.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_sfm.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_stereo.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_structured_light.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_surface_matching.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_tracking.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_xfeatures2d.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_ximgproc.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_xobjdetect.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_xphoto.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_shape.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_phase_unwrapping.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_rgbd.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_calib3d.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_video.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_datasets.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_dnn.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_face.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_plot.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_text.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_features2d.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_flann.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_objdetect.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_ml.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_highgui.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_photo.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_videoio.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_imgcodecs.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_imgproc.3.2.0.dylib
Tracker: /usr/local/lib/libopencv_core.3.2.0.dylib
Tracker: CMakeFiles/Tracker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/coskunyerli/CLionProjects/Visualization/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Tracker"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tracker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tracker.dir/build: Tracker

.PHONY : CMakeFiles/Tracker.dir/build

CMakeFiles/Tracker.dir/requires: CMakeFiles/Tracker.dir/track.cpp.o.requires

.PHONY : CMakeFiles/Tracker.dir/requires

CMakeFiles/Tracker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Tracker.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Tracker.dir/clean

CMakeFiles/Tracker.dir/depend:
	cd /Users/coskunyerli/CLionProjects/Visualization/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/coskunyerli/CLionProjects/Visualization /Users/coskunyerli/CLionProjects/Visualization /Users/coskunyerli/CLionProjects/Visualization/cmake-build-debug /Users/coskunyerli/CLionProjects/Visualization/cmake-build-debug /Users/coskunyerli/CLionProjects/Visualization/cmake-build-debug/CMakeFiles/Tracker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Tracker.dir/depend

