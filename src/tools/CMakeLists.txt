# Minimal CMake version required
cmake_minimum_required(VERSION 3.0.0)

# Find glib-2.0
pkg_check_modules("GLIB" REQUIRED "glib-2.0")
include_directories(${GLIB_INCLUDE_DIRS})

# Build the urlpipe tool executable
add_executable(sterm-urlpipe urlpipe.cpp)
target_link_libraries(sterm-urlpipe sterm-common-messages)
target_link_libraries(sterm-urlpipe sterm-common-xdg)
target_link_libraries(sterm-urlpipe ${GLIB_LIBRARIES})

# Install the sterm binary
install(TARGETS sterm-urlpipe DESTINATION ${CMAKE_INSTALL_BINDIR})

