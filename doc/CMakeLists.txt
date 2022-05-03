# Install data files
install(FILES sterm.ini
        DESTINATION ${CMAKE_INSTALL_DOCDIR})

install(FILES sterm.desktop
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)

if(WITH_TOOLS)
    install(FILES matchmaker.ini
            DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif(WITH_TOOLS)

# Install the man-pages
add_subdirectory(man)

