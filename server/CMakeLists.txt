cmake_minimum_required(VERSION 3.15)

set(CI_PROJECT_NAME "CellsInterlinkedServer")
set(CI_SERVER_VERSION 1.0.0)

project(${CI_PROJECT_NAME}
        VERSION ${CI_SERVER_VERSION})

set(CMAKE_CXX_STANDARD 20)


add_executable(CellsInterlinkedServer ServerMain.cpp)

configure_file(template/meta/BuildInfo.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/generated/meta/BuildInfo.h)
target_include_directories(CellsInterlinkedServer PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/generated/)
