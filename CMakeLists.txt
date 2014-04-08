cmake_minimum_required ( VERSION 2.8.8 )

project ( STerm )

include ( FindPkgConfig )

option ( WITH_LIBRARY "Build the shared library" ON )
option ( WITH_URLPIPE "Build the application to extract urls from a text" ON )

pkg_check_modules ( "VTE" REQUIRED "vte-2.90" )

### sterm-core ################################################################

if ( WITH_LIBRARY )
  add_library ( sterm-core SHARED configuration.c functions.c terminal.c )

  set_target_properties ( sterm-core PROPERTIES INCLUDE_DIRECTORIES "${VTE_INCLUDE_DIRS}" )
  target_link_libraries ( sterm-core ${VTE_LIBRARIES} )

  install ( TARGETS sterm-core DESTINATION lib${LIB_SUFFIX} )
endif ( WITH_LIBRARY )

### sterm #####################################################################
if ( WITH_LIBRARY )
  add_executable ( sterm sterm.c )

  set_target_properties ( sterm PROPERTIES INCLUDE_DIRECTORIES "${VTE_INCLUDE_DIRS}" )
  target_link_libraries ( sterm sterm-core )
else ( WITH_LIBRARY )
  add_executable ( sterm configuration.c functions.c terminal.c sterm.c )

  set_target_properties ( sterm PROPERTIES INCLUDE_DIRECTORIES "${VTE_INCLUDE_DIRS}" )
  target_link_libraries ( sterm ${VTE_LIBRARIES} )
endif ( WITH_LIBRARY )

install ( TARGETS sterm DESTINATION bin )
install ( FILES sterm.ini DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/sterm )

### sterm-urlpipe #############################################################

if ( WITH_URLPIPE )
  pkg_check_modules ( "GIO-UNIX" REQUIRED "gio-unix-2.0" )

  add_executable ( sterm-urlpipe sterm-urlpipe.c )

  set_target_properties ( sterm-urlpipe PROPERTIES INCLUDE_DIRECTORIES "${GIO-UNIX_INCLUDE_DIRS}" )
  target_link_libraries ( sterm-urlpipe ${GIO-UNIX_LIBRARIES} )

  install ( TARGETS sterm-urlpipe DESTINATION bin )
  install ( FILES urlpipe.ini DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/sterm )
endif ( WITH_URLPIPE )
