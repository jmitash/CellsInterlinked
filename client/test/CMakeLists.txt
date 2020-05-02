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
if (CI_CONAN_MANUAL)
    conan_basic_setup()
else ()
    conan_cmake_run(
            CONANFILE conanfile.txt
            BASIC_SETUP
            BUILD missing)
endif ()
########### End Conan Setup and Run ###########

enable_testing()

add_executable(${PROJECT_NAME} "ClientMainTest.cpp" ${CI_SRC_FILES_NO_MAIN}) #TODO: test main
target_include_directories(${PROJECT_NAME} PRIVATE ${CI_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${CI_INHERITED_CONAN_LIBS} ${CONAN_LIBS})