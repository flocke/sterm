cmake_minimum_required( VERSION 2.8.8 )

include( FindPkgConfig )

set(CMAKE_CXX_STANDARD 11)

project( sterm CXX )

option( WITH_TESTS "Build the tests" ON )

include_directories( ${CMAKE_SOURCE_DIR}/include )

add_subdirectory( src )

## Testing
if ( WITH_TESTS )
  add_subdirectory( tests )
  
  enable_testing()
  add_test( NAME parse_config_file COMMAND ${CMAKE_BINARY_DIR}/tests/test_config ${CMAKE_SOURCE_DIR}/tests/test_config.ini )
endif ( WITH_TESTS )

