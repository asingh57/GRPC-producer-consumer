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
CMAKE_SOURCE_DIR = /home/abhi/Desktop/OMSCS/AOS/project3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/abhi/Desktop/OMSCS/AOS/project3/build

# Include any dependencies generated for this target.
include test/CMakeFiles/run_vendors.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/run_vendors.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/run_vendors.dir/flags.make

test/CMakeFiles/run_vendors.dir/vendor.cc.o: test/CMakeFiles/run_vendors.dir/flags.make
test/CMakeFiles/run_vendors.dir/vendor.cc.o: ../test/vendor.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abhi/Desktop/OMSCS/AOS/project3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/run_vendors.dir/vendor.cc.o"
	cd /home/abhi/Desktop/OMSCS/AOS/project3/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run_vendors.dir/vendor.cc.o -c /home/abhi/Desktop/OMSCS/AOS/project3/test/vendor.cc

test/CMakeFiles/run_vendors.dir/vendor.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_vendors.dir/vendor.cc.i"
	cd /home/abhi/Desktop/OMSCS/AOS/project3/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abhi/Desktop/OMSCS/AOS/project3/test/vendor.cc > CMakeFiles/run_vendors.dir/vendor.cc.i

test/CMakeFiles/run_vendors.dir/vendor.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_vendors.dir/vendor.cc.s"
	cd /home/abhi/Desktop/OMSCS/AOS/project3/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abhi/Desktop/OMSCS/AOS/project3/test/vendor.cc -o CMakeFiles/run_vendors.dir/vendor.cc.s

test/CMakeFiles/run_vendors.dir/vendor.cc.o.requires:

.PHONY : test/CMakeFiles/run_vendors.dir/vendor.cc.o.requires

test/CMakeFiles/run_vendors.dir/vendor.cc.o.provides: test/CMakeFiles/run_vendors.dir/vendor.cc.o.requires
	$(MAKE) -f test/CMakeFiles/run_vendors.dir/build.make test/CMakeFiles/run_vendors.dir/vendor.cc.o.provides.build
.PHONY : test/CMakeFiles/run_vendors.dir/vendor.cc.o.provides

test/CMakeFiles/run_vendors.dir/vendor.cc.o.provides.build: test/CMakeFiles/run_vendors.dir/vendor.cc.o


test/CMakeFiles/run_vendors.dir/run_vendors.cc.o: test/CMakeFiles/run_vendors.dir/flags.make
test/CMakeFiles/run_vendors.dir/run_vendors.cc.o: ../test/run_vendors.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abhi/Desktop/OMSCS/AOS/project3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/run_vendors.dir/run_vendors.cc.o"
	cd /home/abhi/Desktop/OMSCS/AOS/project3/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run_vendors.dir/run_vendors.cc.o -c /home/abhi/Desktop/OMSCS/AOS/project3/test/run_vendors.cc

test/CMakeFiles/run_vendors.dir/run_vendors.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_vendors.dir/run_vendors.cc.i"
	cd /home/abhi/Desktop/OMSCS/AOS/project3/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abhi/Desktop/OMSCS/AOS/project3/test/run_vendors.cc > CMakeFiles/run_vendors.dir/run_vendors.cc.i

test/CMakeFiles/run_vendors.dir/run_vendors.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_vendors.dir/run_vendors.cc.s"
	cd /home/abhi/Desktop/OMSCS/AOS/project3/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abhi/Desktop/OMSCS/AOS/project3/test/run_vendors.cc -o CMakeFiles/run_vendors.dir/run_vendors.cc.s

test/CMakeFiles/run_vendors.dir/run_vendors.cc.o.requires:

.PHONY : test/CMakeFiles/run_vendors.dir/run_vendors.cc.o.requires

test/CMakeFiles/run_vendors.dir/run_vendors.cc.o.provides: test/CMakeFiles/run_vendors.dir/run_vendors.cc.o.requires
	$(MAKE) -f test/CMakeFiles/run_vendors.dir/build.make test/CMakeFiles/run_vendors.dir/run_vendors.cc.o.provides.build
.PHONY : test/CMakeFiles/run_vendors.dir/run_vendors.cc.o.provides

test/CMakeFiles/run_vendors.dir/run_vendors.cc.o.provides.build: test/CMakeFiles/run_vendors.dir/run_vendors.cc.o


# Object files for target run_vendors
run_vendors_OBJECTS = \
"CMakeFiles/run_vendors.dir/vendor.cc.o" \
"CMakeFiles/run_vendors.dir/run_vendors.cc.o"

# External object files for target run_vendors
run_vendors_EXTERNAL_OBJECTS =

bin/run_vendors: test/CMakeFiles/run_vendors.dir/vendor.cc.o
bin/run_vendors: test/CMakeFiles/run_vendors.dir/run_vendors.cc.o
bin/run_vendors: test/CMakeFiles/run_vendors.dir/build.make
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libgrpc++.a
bin/run_vendors: external/libp3protolib.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libgrpc.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libssl.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libcrypto.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libz.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libcares.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libre2.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libupb.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libport.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_status.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_cord.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_hash.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_bad_variant_access.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_city.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_raw_hash_set.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_bad_optional_access.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_hashtablez_sampler.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_exponential_biased.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libgpr.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_synchronization.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_stacktrace.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_symbolize.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_debugging_internal.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_demangle_internal.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_graphcycles_internal.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_time.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_civil_time.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_time_zone.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_malloc_internal.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_str_format_internal.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_strings.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_strings_internal.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_int128.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_throw_delegate.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_base.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_raw_logging_internal.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_dynamic_annotations.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_log_severity.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libabsl_spinlock_wait.a
bin/run_vendors: /usr/lib/x86_64-linux-gnu/librt.so
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libaddress_sorting.a
bin/run_vendors: /home/abhi/Desktop/OMSCS/AOS/vcpkg/installed/x64-linux/debug/lib/libprotobufd.a
bin/run_vendors: test/CMakeFiles/run_vendors.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/abhi/Desktop/OMSCS/AOS/project3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../bin/run_vendors"
	cd /home/abhi/Desktop/OMSCS/AOS/project3/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/run_vendors.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/run_vendors.dir/build: bin/run_vendors

.PHONY : test/CMakeFiles/run_vendors.dir/build

test/CMakeFiles/run_vendors.dir/requires: test/CMakeFiles/run_vendors.dir/vendor.cc.o.requires
test/CMakeFiles/run_vendors.dir/requires: test/CMakeFiles/run_vendors.dir/run_vendors.cc.o.requires

.PHONY : test/CMakeFiles/run_vendors.dir/requires

test/CMakeFiles/run_vendors.dir/clean:
	cd /home/abhi/Desktop/OMSCS/AOS/project3/build/test && $(CMAKE_COMMAND) -P CMakeFiles/run_vendors.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/run_vendors.dir/clean

test/CMakeFiles/run_vendors.dir/depend:
	cd /home/abhi/Desktop/OMSCS/AOS/project3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/abhi/Desktop/OMSCS/AOS/project3 /home/abhi/Desktop/OMSCS/AOS/project3/test /home/abhi/Desktop/OMSCS/AOS/project3/build /home/abhi/Desktop/OMSCS/AOS/project3/build/test /home/abhi/Desktop/OMSCS/AOS/project3/build/test/CMakeFiles/run_vendors.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/run_vendors.dir/depend

