cmake_minimum_required(VERSION 3.17)

# Verify the user isn't building in the source directory
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "Building within the source directory is disallowed to prevent accidental corruption of the \
source directory. Please specify a build directory in a different location.")
endif ()

project(CellsInterlinkedClient
        VERSION 1.0.0
        DESCRIPTION "The Cells Interlinked Client")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE CI_SRC_FILES_NO_MAIN CONFIGURE_DEPENDS "src/*/*.h" "src/*/*.cpp")
set(CI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CI_PROJECT_LIB_NAME "${PROJECT_NAME}Sources")


###############################################
############# Conan Setup and Run #############
###############################################
if (CI_CONAN_MANUAL)
    set(CI_CONANBUILDINFO_FILE ${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    if (NOT EXISTS ${CI_CONANBUILDINFO_FILE})
        message(FATAL_ERROR "Could not find the conanbuildinfo.cmake file. Perhaps you need to run a 'conan install'?")
    endif ()
    include(${CI_CONANBUILDINFO_FILE})
    conan_basic_setup()
else ()
    set(CI_CONAN_CMAKE_FILE ${CMAKE_CURRENT_BINARY_DIR}/conan.cmake)
    if (NOT EXISTS ${CI_CONAN_CMAKE_FILE})
        set(CI_CONAN_CMAKE_FILE_URL "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake")
        message(STATUS "Downloading conan.cmake from ${CI_CONAN_CMAKE_FILE_URL}")
        file(DOWNLOAD "${CI_CONAN_CMAKE_FILE_URL}" ${CI_CONAN_CMAKE_FILE})
    endif ()
    include(${CI_CONAN_CMAKE_FILE})
    conan_cmake_run(
            CONANFILE conanfile.txt
            BASIC_SETUP
            BUILD missing)
endif ()
########### End Conan Setup and Run ###########


add_library(${CI_PROJECT_LIB_NAME} ${CI_SRC_FILES_NO_MAIN})
target_include_directories(${CI_PROJECT_LIB_NAME} PUBLIC ${CI_INCLUDE_DIR})
target_link_libraries(${CI_PROJECT_LIB_NAME} ${CONAN_LIBS})

add_subdirectory(src)
add_subdirectory(test)