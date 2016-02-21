# Minimal CMake version required
cmake_minimum_required(VERSION 2.8.8)

# Build the main executable
add_executable(sterm main.cpp)
target_link_libraries(sterm sterm_lib)

# Install the sterm binary
install(TARGETS sterm DESTINATION ${CMAKE_INSTALL_BINDIR})

