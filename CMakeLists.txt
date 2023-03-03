# Minimal CMake version required
cmake_minimum_required(VERSION 3.23)

# Use the C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project name
project(
    sterm
    VERSION 0.1.2
    DESCRIPTION "Minimal terminal emulator for linux"
    LANGUAGES CXX
)

# CMake modules
include(FindPkgConfig)
include(GNUInstallDirs)

# Build options
option(WITH_TOOLS "Build some helper tools, mainly usefull for keybindings" ON)

# Find external dependencies
pkg_check_modules("glib2" REQUIRED IMPORTED_TARGET "glib-2.0")
pkg_check_modules("vte" REQUIRED IMPORTED_TARGET "vte-2.91")

# Main source files
add_subdirectory(doc)
add_subdirectory(src)
