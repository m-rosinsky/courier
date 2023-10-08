cmake_minimum_required(VERSION 3.10)

# Project name.
project(courier)

# Specify C++ standard.
set(CMAKE_CXX_STANDARD 11)

# Specify sources.
set(SOURCES
    src/main.cpp
)

# Add executable target.
add_executable(${PROJECT_NAME} ${SOURCES})

# Version data.
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)
