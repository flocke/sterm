# Minimal CMake version required
cmake_minimum_required(VERSION 3.0.0)

# Install data files
install(FILES sterm.ini DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(FILES sterm.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)

# Install the man-pages
add_subdirectory(man)

