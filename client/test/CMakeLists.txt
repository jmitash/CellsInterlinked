cmake_minimum_required(VERSION 3.17)

project(${PROJECT_NAME}Test
        VERSION ${PROJECT_VERSION}
        DESCRIPTION "${PROJECT_DESCRIPTION} Tests")

###############################################
############# Conan Setup and Run #############
###############################################
# Temporary fix for conan.cmake 0.15
get_directory_property(CI_ORIG_COMPILE_OPTIONS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMPILE_OPTIONS)
string(GENEX_STRIP "${CI_ORIG_COMPILE_OPTIONS}" CI_STRIPPED_COMPILE_OPTIONS)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY COMPILE_OPTIONS ${CI_STRIPPED_COMPILE_OPTIONS})
# End temporary fix

set(CI_INHERITED_CONAN_LIBS ${CONAN_LIBS})
if (CONAN_MANUAL)
    conan_basic_setup()
else ()
    conan_cmake_run(
            CONANFILE conanfile.txt
            BASIC_SETUP
            BUILD missing)
endif ()
########### End Conan Setup and Run ###########

file(GLOB_RECURSE CI_TEST_FILES CONFIGURE_DEPENDS "*.h" "*.cpp")
add_executable(${PROJECT_NAME} ${CI_TEST_FILES})
target_link_libraries(${PROJECT_NAME} ${CI_PROJECT_LIB_NAME} ${CONAN_LIBS})

if (${RUN_TESTS})
    message(STATUS "Will run tests.")
    add_custom_command(
            TARGET ${PROJECT_NAME}
            COMMENT "Running tests for ${PROJECT_NAME}"
            POST_BUILD
            COMMAND ${PROJECT_NAME})
else ()
    message(STATUS "Not running tests.")
endif ()