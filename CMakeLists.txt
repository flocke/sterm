# Minimal CMake version required
cmake_minimum_required(VERSION 3.7..3.23)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Use the C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project name
project(sterm   VERSION 0.1.2
                DESCRIPTION "Minimal terminal emulator for linux"
                LANGUAGES CXX)

# CMake modules
include(FindPkgConfig)
include(GNUInstallDirs)

# Build options
option(WITH_TOOLS "Build some helper tools, mainly usefull for keybindings" ON)

# Main source files
add_subdirectory(doc)
add_subdirectory(src)

