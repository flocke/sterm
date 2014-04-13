cmake_minimum_required ( VERSION 2.8.8 )

project ( STerm )

include ( FindPkgConfig )

option ( WITH_LIBRARY "Build the shared library" ON )
option ( WITH_URLPIPE "Build the application to extract urls from a text" ON )

set ( BIN_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin )
set ( DOC_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/doc/sterm )
set ( LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX} )
set ( MAN_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/man/man1 )

include_directories ( ${CMAKE_SOURCE_DIR}/include )

add_subdirectory ( sterm )
add_subdirectory ( tools )
add_subdirectory ( doc )
