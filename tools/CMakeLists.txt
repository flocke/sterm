cmake_minimum_required ( VERSION 2.8.8 )

project ( STerm )

if ( WITH_URLPIPE )
  add_subdirectory ( urlpipe )
endif ( WITH_URLPIPE )
