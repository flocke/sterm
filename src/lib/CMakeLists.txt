# Minimal CMake version required
cmake_minimum_required(VERSION 2.8.8)

# Build the shared library
if (WITH_LIBRARY)
  add_library(sterm_lib SHARED config.cpp function_handler.cpp functions.cpp misc.cpp terminal.cpp)

  target_link_libraries(sterm_lib ${VTE_LIBRARIES})

  set_target_properties(sterm_lib PROPERTIES OUTPUT_NAME sterm)
  set_target_properties(sterm_lib PROPERTIES VERSION ${STERM_VERSION_STRING})
  set_target_properties(sterm_lib PROPERTIES SOVERSION ${STERM_VERSION_MAJOR})

  install(TARGETS sterm_lib DESTINATION ${CMAKE_INSTALL_LIBDIR})
else (WITH_LIBRARY)
  add_library(sterm_lib STATIC config.cpp function_handler.cpp functions.cpp misc.cpp terminal.cpp)

  target_link_libraries(sterm_lib ${VTE_LIBRARIES})
endif(WITH_LIBRARY)

