cmake_minimum_required ( VERSION 2.8.8 )

project ( STerm )

pkg_check_modules ( "GIO-UNIX" REQUIRED "gio-unix-2.0" )

include_directories ( ${GIO-UNIX_INCLUDE_DIRS} )

add_executable ( sterm-urlpipe urlpipe.c )

target_link_libraries ( sterm-urlpipe ${GIO-UNIX_LIBRARIES} )

install ( TARGETS sterm-urlpipe DESTINATION ${BIN_INSTALL_DIR} )
install ( FILES sterm-urlpipe.1 DESTINATION ${MAN_INSTALL_DIR} )
