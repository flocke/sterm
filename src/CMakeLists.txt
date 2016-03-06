# Minimal CMake version required
cmake_minimum_required(VERSION 3.0.0)

# Set the include dir
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/main)

# Subdirectories
add_subdirectory(common)
add_subdirectory(main)

if(WITH_TOOLS)
  add_subdirectory(tools)
endif(WITH_TOOLS)

