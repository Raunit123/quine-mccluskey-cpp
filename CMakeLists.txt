cmake_minimum_required(VERSION 3.10)
project(QuineMcCluskey)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/qm.cpp
    src/main.cpp
)

# Create executable
add_executable(qm ${SOURCES})