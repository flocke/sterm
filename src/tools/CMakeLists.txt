# Find glib-2.0
pkg_check_modules("GLIB" REQUIRED "glib-2.0")

# Build the matchmaker tool
add_executable(sterm-matchmaker matchmaker.cpp)
target_include_directories(sterm-matchmaker PRIVATE ${GLIB_INCLUDE_DIRS})
target_link_libraries(sterm-matchmaker PRIVATE sterm-common-messages
                                       PRIVATE sterm-common-xdg
                                       PRIVATE ${GLIB_LIBRARIES})

# Install the matchmaker binary
install(TARGETS sterm-matchmaker
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

