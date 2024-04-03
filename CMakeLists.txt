# At LEAST 3.9 but newer is better
cmake_minimum_required(VERSION 3.11)

# Assign a name to the global project
project(spectrogram)

# Set the version of C/C++ (here C++17)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(cmsis)

file(GLOB SRC src/*.c src/*.cpp src/*.h)

add_executable(main ${SRC})

target_link_libraries(main CMSISDSP)