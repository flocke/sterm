# Minimal CMake version required
cmake_minimum_required(VERSION 3.0.0)

# Subdirectories
add_subdirectory(app)
add_subdirectory(lib)

if(WITH_TOOLS)
  add_subdirectory(tools)
endif(WITH_TOOLS)
