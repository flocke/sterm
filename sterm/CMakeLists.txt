cmake_minimum_required ( VERSION 2.8.8 )

project ( STerm )

pkg_check_modules ( "VTE" REQUIRED "vte-2.90" )

include_directories ( ${VTE_INCLUDE_DIRS} )

if ( WITH_LIBRARY )
  add_library ( sterm-core SHARED configuration.c functions.c terminal.c )
  add_executable ( sterm sterm.c )

  target_link_libraries ( sterm-core ${VTE_LIBRARIES} )
  target_link_libraries ( sterm sterm-core )

  install ( TARGETS sterm-core DESTINATION ${LIB_INSTALL_DIR} )
else ( WITH_LIBRARY )
  add_executable ( sterm configuration.c functions.c terminal.c sterm.c )

  target_link_libraries ( sterm ${VTE_LIBRARIES} )
endif ( WITH_LIBRARY )

install ( TARGETS sterm DESTINATION ${BIN_INSTALL_DIR} )
