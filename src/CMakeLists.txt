# Minimal CMake version required
cmake_minimum_required(VERSION 3.0.0)

# Subdirectories
add_subdirectory(common)
add_subdirectory(sterm)

if(WITH_TOOLS)
  add_subdirectory(tools)
endif(WITH_TOOLS)

