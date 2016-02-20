cmake_minimum_required( VERSION 2.8.8 )

project( sterm_tests CXX )

pkg_check_modules( "VTE" REQUIRED "vte-2.91" )

include_directories( ${VTE_INCLUDE_DIRS} )

add_executable( test_config config.cpp )
target_link_libraries( test_config sterm )

