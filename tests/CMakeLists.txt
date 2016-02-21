# Minimal CMake version required
cmake_minimum_required( VERSION 2.8.8 )

# Find the VTE library (version 2.91)
pkg_check_modules( "VTE" REQUIRED "vte-2.91" )
include_directories( ${VTE_INCLUDE_DIRS} )

# Build the test for the config file parser
add_executable( test_config config.cpp )
target_link_libraries( test_config sterm_lib )

