# Find glib-2.0
pkg_check_modules("GLIB" REQUIRED "glib-2.0")

set(COMPONENT_NAME "${PROJECT_NAME}-common")

add_library(${COMPONENT_NAME} STATIC)
add_library(${PROJECT_NAME}::common ALIAS ${COMPONENT_NAME})

target_sources(
    ${COMPONENT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/messages.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/strsplit.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/xdg.cpp
)

target_include_directories(
    ${COMPONENT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/inc
    PRIVATE
        ${GLIB_INCLUDE_DIRS}
)

target_link_libraries(
    ${COMPONENT_NAME}
    PRIVATE
        ${GLIB_LIBRARIES}
)
