cmake_minimum_required(VERSION 3.15)

set(CI_PROJECT_NAME "CellsInterlinkedServer")
set(CI_SERVER_VERSION 1.0.0)

project(${CI_PROJECT_NAME}
        VERSION ${CI_SERVER_VERSION})

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE CI_SERVER_SRCFILES
        "*.h"
        "*.cpp")

add_executable(CellsInterlinkedServer ${CI_SERVER_SRCFILES})

configure_file(template/meta/BuildInfo.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/generated/meta/BuildInfo.h)
target_include_directories(CellsInterlinkedServer PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/generated/)
