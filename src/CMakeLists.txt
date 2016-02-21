# Minimal CMake version required
cmake_minimum_required( VERSION 2.8.8 )

# Find the VTE library (version 2.91)
pkg_check_modules( "VTE" REQUIRED "vte-2.91" )
include_directories( ${VTE_INCLUDE_DIRS} )

# Build the shared library
add_library(sterm_lib SHARED config.cpp terminal.cpp)
target_link_libraries(sterm_lib ${VTE_LIBRARIES})
set_target_properties(sterm_lib PROPERTIES OUTPUT_NAME sterm)
set_target_properties(sterm_lib PROPERTIES VERSION ${STERM_VERSION_STRING})
set_target_properties(sterm_lib PROPERTIES SOVERSION ${STERM_VERSION_MAJOR})

# Build the main executable
add_executable(sterm main.cpp)
target_link_libraries(sterm sterm_lib)

