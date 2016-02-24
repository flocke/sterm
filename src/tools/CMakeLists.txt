# Minimal CMake version required
cmake_minimum_required(VERSION 2.8.8)

# Find glib2
pkg_check_modules("GLIB" REQUIRED "glib-2.0")
include_directories(${GLIB_INCLUDE_DIRS})

# Build the urlpipe executable
add_executable(sterm-urlpipe ../lib/misc.cpp urlpipe.cpp)
target_link_libraries(sterm-urlpipe ${GLIB_LIBRARIES})

# Install the sterm binary
install(TARGETS sterm-urlpipe DESTINATION ${CMAKE_INSTALL_BINDIR})

