# Minimal CMake version required
cmake_minimum_required(VERSION 2.8.8)

# Find vte-2.91
pkg_check_modules("VTE" REQUIRED "vte-2.91")
include_directories(${VTE_INCLUDE_DIRS})

# Build the main executable
add_executable(sterm main.cpp)
target_link_libraries(sterm libsterm)

# Install the sterm binary
install(TARGETS sterm DESTINATION ${CMAKE_INSTALL_BINDIR})

