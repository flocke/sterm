cmake_minimum_required ( VERSION 2.8.8 )

project ( STerm )

install ( FILES sterm.ini DESTINATION ${CMAKE_INSTALL_DOCDIR} )
install ( FILES sterm.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1 )
install ( FILES sterm.ini.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1 )
install ( FILES sterm.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications )
