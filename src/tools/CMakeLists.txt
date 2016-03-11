# Minimal CMake version required
cmake_minimum_required(VERSION 3.0.0)

# Find glib-2.0
pkg_check_modules("GLIB" REQUIRED "glib-2.0")
include_directories(${GLIB_INCLUDE_DIRS})

# Build the matchmaker tool
add_executable(sterm-matchmaker matchmaker.cpp)
target_link_libraries(sterm-matchmaker sterm-common-messages)
target_link_libraries(sterm-matchmaker sterm-common-xdg)
target_link_libraries(sterm-matchmaker ${GLIB_LIBRARIES})

# Install the matchmaker binary
install(TARGETS sterm-matchmaker DESTINATION ${CMAKE_INSTALL_BINDIR})

