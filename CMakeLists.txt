# Minimal CMake version required
cmake_minimum_required(VERSION 2.8.8)

# CMake modules
include(FindPkgConfig)
include(GNUInstallDirs)

# Use the C++11 standard
set(CMAKE_CXX_STANDARD 11)

# Main project (use C++)
project(sterm CXX)

# Version 0.1.0
set(STERM_VERSION_MAJOR 0)
set(STERM_VERSION_MINOR 1)
set(STERM_VERSION_PATCH 0)
set(STERM_VERSION_STRING ${STERM_VERSION_MAJOR}.${STERM_VERSION_MINOR}.${STERM_VERSION_PATCH})

# Build options
option(WITH_TESTS "Build the (very basic) tests" ON)
option(WITH_LIBRARY "Build and install the shared library" OFF)

# Project include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Main source files
add_subdirectory(src)

# Testing
if (WITH_TESTS)
  # Build the tests
  add_subdirectory(tests)
  
  # Enable CMake testing (ctest)
  enable_testing()
  add_test(NAME parse_config_file COMMAND ${CMAKE_BINARY_DIR}/tests/test_config ${CMAKE_SOURCE_DIR}/tests/test_config.ini)
endif (WITH_TESTS)

