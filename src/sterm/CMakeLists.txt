# Minimal CMake version required
cmake_minimum_required(VERSION 3.0.0)

# Find vte-2.91
pkg_check_modules("VTE" REQUIRED "vte-2.91")
include_directories(${VTE_INCLUDE_DIRS})

# Build all functions into one static library
add_library(sterm-static-lib STATIC config.cpp function_handler.cpp functions.cpp terminal.cpp)
target_link_libraries(sterm-static-lib sterm-common-strsplit)

# Build the main binary
add_executable(sterm main.cpp)
target_link_libraries(sterm sterm-static-lib)
target_link_libraries(sterm sterm-common-messages)
target_link_libraries(sterm sterm-common-xdg)
target_link_libraries(sterm ${VTE_LIBRARIES})

# Install the sterm binary
install(TARGETS sterm DESTINATION ${CMAKE_INSTALL_BINDIR})

