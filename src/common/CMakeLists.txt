# Minimal CMake version required
cmake_minimum_required(VERSION 3.0.0)

# Find glib-2.0
pkg_check_modules("GLIB" REQUIRED "glib-2.0")
include_directories(${GLIB_INCLUDE_DIRS})

# Build the static libraries
add_library(sterm-common-messages STATIC messages.cpp)
add_library(sterm-common-strsplit STATIC strsplit.cpp)
add_library(sterm-common-xdg STATIC xdg.cpp)

target_link_libraries(sterm-common-xdg ${GLIB_LIBRARIES})

