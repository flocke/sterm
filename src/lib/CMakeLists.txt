# Minimal CMake version required
cmake_minimum_required(VERSION 2.8.8)

# Find vte-2.91
pkg_check_modules("VTE" REQUIRED "vte-2.91")
include_directories(${VTE_INCLUDE_DIRS})

# Build the shared library
if (WITH_LIBRARY)
  add_library(libsterm SHARED config.cpp function_handler.cpp functions.cpp misc.cpp terminal.cpp)

  target_link_libraries(libsterm ${VTE_LIBRARIES})

  set_target_properties(libsterm PROPERTIES OUTPUT_NAME sterm)
  set_target_properties(libsterm PROPERTIES VERSION ${STERM_VERSION_STRING})
  set_target_properties(libsterm PROPERTIES SOVERSION ${STERM_VERSION_MAJOR})

  install(TARGETS libsterm DESTINATION ${CMAKE_INSTALL_LIBDIR})
else (WITH_LIBRARY)
  add_library(libsterm STATIC config.cpp function_handler.cpp functions.cpp misc.cpp terminal.cpp)

  target_link_libraries(libsterm ${VTE_LIBRARIES})
endif(WITH_LIBRARY)

