# Minimal CMake version required
cmake_minimum_required(VERSION 3.0.0)

# Replace variables in the man-pages
configure_file(sterm.1.in sterm.1 @ONLY)
configure_file(sterm.ini.1.in sterm.ini.1 @ONLY)

# Install man-pages
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sterm.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sterm.ini.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

# Install man-pages for the tools
if(WITH_TOOLS)
  configure_file(sterm-urlpipe.1.in sterm-urlpipe.1 @ONLY)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sterm-urlpipe.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
endif(WITH_TOOLS)

