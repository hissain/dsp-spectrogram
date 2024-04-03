#!/bin/bash

# Remove the build directory and its contents
rm -rf build

# Delete all CMake cache files
find . -name CMakeCache.txt -type f -delete

# Delete all CMake-generated configuration files
find . -name CMakeFiles -type d -exec rm -rf {} +

# Delete all CMake-generated cmake_install.cmake files
find . -name cmake_install.cmake -type f -delete

# Delete all CMakeLists.txt.user files (if any)
find . -name CMakeLists.txt.user -type f -delete

# Delete all Makefiles
find . -name Makefile -type f -delete
