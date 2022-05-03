# Find glib-2.0
pkg_check_modules("GLIB" REQUIRED "glib-2.0")

# Build the static libraries
add_library(sterm-common-messages STATIC messages.cpp)
add_library(sterm-common-strsplit STATIC strsplit.cpp)
add_library(sterm-common-xdg STATIC xdg.cpp)

target_include_directories(sterm-common-messages PUBLIC ../../include)
target_include_directories(sterm-common-strsplit PUBLIC ../../include)
target_include_directories(sterm-common-xdg PUBLIC ../../include
                                            PUBLIC ${GLIB_INCLUDE_DIRS})

target_link_libraries(sterm-common-xdg PRIVATE ${GLIB_LIBRARIES})

