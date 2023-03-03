# Find glib-2.0
pkg_check_modules("GLIB" REQUIRED "glib-2.0")

set(COMPONENT_NAME "${PROJECT_NAME}-matchmaker")

add_executable(${COMPONENT_NAME})

target_sources(
    ${COMPONENT_NAME}
     PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/matchmaker.cpp
)

target_include_directories(
    ${COMPONENT_NAME}
    PRIVATE
        ${GLIB_INCLUDE_DIRS}
)

target_link_libraries(
    ${COMPONENT_NAME}
    PRIVATE
        sterm::common
        ${GLIB_LIBRARIES}
)

install(
    TARGETS ${COMPONENT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
