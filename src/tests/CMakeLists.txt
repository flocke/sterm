# Minimal CMake version required
cmake_minimum_required(VERSION 3.0.0)

# Find vte-2.91
pkg_check_modules("VTE" REQUIRED "vte-2.91")
include_directories(${VTE_INCLUDE_DIRS})

# Build the test for the config file parser
add_executable(sterm-test-config config.cpp)
target_link_libraries(sterm-test-config sterm-static-lib)
target_link_libraries(sterm-test-config ${VTE_LIBRARIES})

