cmake_minimum_required(VERSION 3.15)

project(CellsInterlinked)

# Resolve the binary directories for subdirectories based off of the build type
if (${CMAKE_BUILD_TYPE} MATCHES "Debug" OR ${PROJECT_BINARY_DIR} MATCHES "debug/?$")
    message(STATUS "Debug build type")
    set(CI_CLIENT_BUILD_DIR "${PROJECT_SOURCE_DIR}/client/build/debug")
    set(CI_SERVER_BUILD_DIR "${PROJECT_SOURCE_DIR}/server/build/debug")
elseif (${CMAKE_BUILD_TYPE} MATCHES "Release" OR ${PROJECT_BINARY_DIR} MATCHES "release/?$")
    message(STATUS "Release build type")
    set(CI_CLIENT_BUILD_DIR "${PROJECT_SOURCE_DIR}/client/build/release")
    set(CI_SERVER_BUILD_DIR "${PROJECT_SOURCE_DIR}/server/build/release")
else ()
    message(FATAL_ERROR "Unknown build type. Build type is required to be \"Debug\" or \"Release\".")
endif ()

set(CI_CLIENT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/client")
set(CI_SERVER_SOURCE_DIR "${PROJECT_SOURCE_DIR}/server")

message(VERBOSE "Adding client source subdirectory ${CI_CLIENT_SOURCE_DIR} with build directory ${CI_CLIENT_BUILD_DIR}")
message(VERBOSE "Adding server source subdirectory ${CI_SERVER_SOURCE_DIR} with build directory ${CI_SERVER_BUILD_DIR}")

add_subdirectory(${CI_CLIENT_SOURCE_DIR} ${CI_CLIENT_BUILD_DIR})
add_subdirectory(${CI_SERVER_SOURCE_DIR} ${CI_SERVER_BUILD_DIR})