cmake_minimum_required(VERSION 3.17)

# Verify the user isn't building in the source directory
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "Building within the source directory is disallowed to prevent accidental corruption of the \
source directory. Please specify a build directory in a different location.")
endif ()

project(CellsInterlinked
        DESCRIPTION "Cross-machine mouse and keyboard control")

add_subdirectory(client)
#add_subdirectory(server)