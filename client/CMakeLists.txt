cmake_minimum_required(VERSION 3.17)

# Verify the user isn't building in the source directory
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "Building within the source directory is disallowed to prevent accidental corruption of the \
source directory. Please specify a build directory in a different location.")
endif ()

set(DEFAULT_BUILD_TYPE "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif ()

project(CellsInterlinkedClient
        VERSION 1.0.0
        DESCRIPTION "The Cells Interlinked Client")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

###############################################
################### Options ###################
###############################################
option(CONAN_MANUAL "If ON, the automatic run of conan install will be skipped. However Conan packages are still
required and must be installed manually. Be mindful of nested directories." OFF)
option(IGNORE_UNSUPPORTED_PLATFORM "Try to compile regardless of the platform being unsupported. This will
almost certainly break things when trying to actually run the executable." OFF)
option(SKIP_BUILD_TESTS "Whether building tests should be skipped." OFF)

option(RUN_TESTS "Whether to run tests after build. SKIP_BUILD_TESTS must be ON." OFF)
if (${RUN_TESTS} AND ${SKIP_BUILD_TESTS})
    message(FATAL_ERROR "Cannot specify SKIP_BUILD_TESTS and RUN_TESTS at the same time.")
endif ()
################# End Options #################

###############################################
############### Configure files ###############
###############################################
# This is where we handle template files
file(GLOB_RECURSE CI_TEMPLATE_SRCFILES
        RELATIVE ${CI_INCLUDE_DIR}
        CONFIGURE_DEPENDS "*.in")
foreach (CI_TEMPLATE_SRCFILE IN ITEMS ${CI_TEMPLATE_SRCFILES})
    # Remove .in
    string(REGEX REPLACE "\\.in$" "" CI_TEMPLATE_DESTFILE ${CI_TEMPLATE_SRCFILE})
    # Put in generated/ subdirectory
    set(CI_TEMPLATE_DESTFILE "generated/${CI_TEMPLATE_DESTFILE}")
    message(VERBOSE "Template file will be configured: ${CI_TEMPLATE_SRCFILE} --- ${CI_TEMPLATE_DESTFILE}")
    configure_file("${CI_INCLUDE_DIR}/${CI_TEMPLATE_SRCFILE}" ${CI_TEMPLATE_DESTFILE})
endforeach ()
set(CI_GENERATED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
if (NOT EXISTS ${CI_GENERATED_INCLUDE_DIR})
    set(CI_GENERATED_INCLUDE_DIR "")
endif ()
############# End Configure files #############

###############################################
############# Conan Setup and Run #############
###############################################
if (CONAN_MANUAL)
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


###############################################
############ Library Configuration ############
###############################################
file(GLOB_RECURSE CI_SRC_FILES_NO_MAIN CONFIGURE_DEPENDS "src/*/*.h" "src/*/*.cpp")
set(CI_PROJECT_LIB_NAME "${PROJECT_NAME}Sources")

add_library(${CI_PROJECT_LIB_NAME} ${CI_SRC_FILES_NO_MAIN})
target_include_directories(${CI_PROJECT_LIB_NAME} PUBLIC ${CI_INCLUDE_DIR} ${CI_GENERATED_INCLUDE_DIR})
target_link_libraries(${CI_PROJECT_LIB_NAME} ${CONAN_LIBS})
########## End Library Configuration ##########


###############################################
#### Subdirectories (executable and tests) ####
###############################################
add_subdirectory(src)
if (NOT ${SKIP_BUILD_TESTS})
    message(STATUS "Will build tests.")
    enable_testing()
    add_subdirectory(test)
else ()
    message(STATUS "Skipping tests because SKIP_BUILD_TESTS was set to ${SKIP_BUILD_TESTS}.")
endif ()
## End Subdirectories (executable and tests) ##