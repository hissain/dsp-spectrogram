# At LEAST 3.9 but newer is better
cmake_minimum_required(VERSION 3.11)

# Assign a name to the global project
project(spectrogram)

# Load all the source file within the folder src
file(GLOB SOURCE_FILES_SPECT src/*.cpp src/*.c src/*.h)

# Add static library
add_library(cmsisdsp STATIC IMPORTED)
set_target_properties(cmsisdsp PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libCMSISDSP.a)

# Define the executable of the application !
add_executable(main ${SOURCE_FILES_SPECT})

# Indicate that the app uses the header files within the folder include.
# Using target_include_directories instead of include_directories enables CMake to
# transitively make available the header files in the projects that depend on this library.
target_include_directories(main PUBLIC inc)
target_include_directories(main PUBLIC inc/core)
target_include_directories(main PUBLIC inc/dsp)

# Indicate that the application depends on the library math
target_link_libraries(main cmsisdsp)

# 'm' for including math library explicitly
target_link_libraries(main m) 
