cmake_minimum_required ( VERSION 2.6 )

project ( STerm )

include ( FindPkgConfig )

pkg_check_modules ( "VTE" REQUIRED "vte-2.90" )

include_directories ( ${VTE_INCLUDE_DIRS} )

add_executable ( sterm terminal.c configuration.c main.c )

target_link_libraries ( sterm ${VTE_LIBRARIES} )

install ( TARGETS sterm DESTINATION bin )
install ( FILES sterm.ini DESTINATION ${CMAKE_INSTALL_PREFIX}/share/sterm )
