cmake_minimum_required(VERSION 3.15)

project(CellsInterlinked
        VERSION 1.0.0)

set(PROJECT_BINARY_DIR "output")
set(PROJECT_BINARY_DIR "output")

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    message("Debug build")
    set(CI_CLIENT_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/client/output/debug")
    set(CI_SERVER_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/server/output/debug")
elseif(${CMAKE_BUILD_TYPE} MATCHES Release)
    message("Release build")
    set(CI_CLIENT_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/client/output/release")
    set(CI_SERVER_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/server/output/release")
endif()

add_subdirectory("${PROJECT_SOURCE_DIR}/client" "${CI_CLIENT_OUTPUT_DIR}")
add_subdirectory("${PROJECT_SOURCE_DIR}/server" "${CI_SERVER_OUTPUT_DIR}")