# Minimal CMake version required
cmake_minimum_required(VERSION 3.0.0)

# Use the C++11 standard
set(CMAKE_CXX_STANDARD 11)

# Project name
project(sterm VERSION 0.1.2 LANGUAGES CXX)

# CMake modules
include(FindPkgConfig)
include(GNUInstallDirs)

# Build options
option(WITH_TESTS "Build the (very basic) tests" OFF)
option(WITH_TOOLS "Build some helper tools, mainly usefull for keybindings" ON)

# Main source files
add_subdirectory(doc)
add_subdirectory(src)

#Testing
if(WITH_TESTS)
  # Enable CMake testing (ctest)
  enable_testing()

  # Add the different tests to run
  add_test(NAME parse_config_file COMMAND ${CMAKE_BINARY_DIR}/src/tests/sterm-test-config ${CMAKE_SOURCE_DIR}/tests/parse_config_file.ini)
endif(WITH_TESTS)

