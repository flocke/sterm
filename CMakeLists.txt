cmake_minimum_required ( VERSION 2.6 )

project ( STerm )

include ( FindPkgConfig )

pkg_check_modules ( "VTE" REQUIRED "vte-2.90" )

include_directories ( ${VTE_INCLUDE_DIRS} )

option ( WITH_LIBRARY "Build the shared library" ON )

if ( WITH_LIBRARY )
  add_library ( sterm-core SHARED configuration.c functions.c terminal.c )
  add_executable ( sterm main.c )

  target_link_libraries ( sterm-core ${VTE_LIBRARIES} )
  target_link_libraries ( sterm sterm-core )

  install ( TARGETS sterm-core DESTINATION lib${LIB_SUFFIX} )
else ( WITH_LIBRARY )
  add_executable ( sterm configuration.c functions.c terminal.c main.c )

  target_link_libraries ( sterm ${VTE_LIBRARIES} )
endif ( WITH_LIBRARY )

install ( TARGETS sterm DESTINATION bin )
install ( FILES sterm.ini DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/sterm )
