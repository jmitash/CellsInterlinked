cmake_minimum_required(VERSION 3.15)

set(CI_PROJECT_NAME "CellsInterlinkedClient")
set(CI_CLIENT_VERSION 1.0.0)


project(${CI_PROJECT_NAME}
        VERSION ${CI_CLIENT_VERSION})

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE CI_CLIENT_SRCFILES
        "*.h"
        "*.cpp")

add_executable(CellsInterlinkedClient ${CI_CLIENT_SRCFILES})

configure_file(template/meta/BuildInfo.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/generated/meta/BuildInfo.h)
target_include_directories(CellsInterlinkedClient PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/generated/)
