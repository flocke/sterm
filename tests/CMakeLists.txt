# Minimal CMake version required
cmake_minimum_required(VERSION 2.8.8)

# Build the test for the config file parser
add_executable(test_config config.cpp)
target_link_libraries(test_config sterm_lib)

