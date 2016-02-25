# Minimal CMake version required
cmake_minimum_required(VERSION 3.0.0)

# Install headers
install(FILES config.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sterm)
install(FILES function_handler.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sterm)
install(FILES functions.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sterm)
install(FILES misc.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sterm)
install(FILES terminal.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sterm)

