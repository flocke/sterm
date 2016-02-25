# Minimal CMake version required
cmake_minimum_required(VERSION 3.0.0)

# Find vte-2.91
pkg_check_modules("VTE" REQUIRED "vte-2.91")
include_directories(${VTE_INCLUDE_DIRS})

# Build the shared library
add_library(libsterm SHARED config.cpp function_handler.cpp functions.cpp misc.cpp terminal.cpp)
target_link_libraries(libsterm ${VTE_LIBRARIES})

set_target_properties(libsterm PROPERTIES OUTPUT_NAME sterm)
set_target_properties(libsterm PROPERTIES VERSION ${sterm_VERSION})
set_target_properties(libsterm PROPERTIES SOVERSION ${sterm_VERSION_MAJOR})

# Install the sterm library
install(TARGETS libsterm DESTINATION ${CMAKE_INSTALL_LIBDIR})

