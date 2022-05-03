# Find vte-2.91
pkg_check_modules("VTE" REQUIRED "vte-2.91")

# Build the main binary
add_executable(sterm main.cpp config.cpp function_handler.cpp functions.cpp terminal.cpp)
target_include_directories(sterm PRIVATE ${VTE_INCLUDE_DIRS})
target_link_libraries(sterm PRIVATE sterm-common-messages
                            PRIVATE sterm-common-strsplit
                            PRIVATE sterm-common-xdg
                            PRIVATE ${VTE_LIBRARIES})

# Install the sterm binary
install(TARGETS sterm
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

