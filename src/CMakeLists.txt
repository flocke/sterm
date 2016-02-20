cmake_minimum_required( VERSION 2.8.8 )

project( sterm_main CXX )

pkg_check_modules( "VTE" REQUIRED "vte-2.91" )

include_directories( ${VTE_INCLUDE_DIRS} )

add_library( sterm SHARED config.cpp )
target_link_libraries( sterm ${VTE_LIBRARIES} )

