set(COMPONENT_NAME "${PROJECT_NAME}-matchmaker")

add_executable(${COMPONENT_NAME})

target_sources(
    ${COMPONENT_NAME}
     PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/matchmaker.cpp
)

target_link_libraries(
    ${COMPONENT_NAME}
    PRIVATE
        sterm::common
        PkgConfig::glib2
)

install(
    TARGETS ${COMPONENT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
