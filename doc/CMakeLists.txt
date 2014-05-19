cmake_minimum_required ( VERSION 2.8.8 )

project ( STerm )

install ( FILES sterm.ini DESTINATION ${DOC_INSTALL_DIR} )
install ( FILES sterm.1 DESTINATION ${MAN_INSTALL_DIR} )
install ( FILES sterm.ini.1 DESTINATION ${MAN_INSTALL_DIR} )
install ( FILES sterm.desktop DESTINATION ${DESKTOP_INSTALL_DIR} )
