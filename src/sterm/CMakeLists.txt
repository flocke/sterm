set(COMPONENT_NAME ${PROJECT_NAME})

add_executable(${COMPONENT_NAME})

target_sources(
    ${COMPONENT_NAME}
     PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/config.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/function_handler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/functions.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/terminal.cpp
)

target_include_directories(
    ${COMPONENT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    ${COMPONENT_NAME}
    PRIVATE
        sterm::common
        PkgConfig::vte
)

install(
    TARGETS ${COMPONENT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
