cmake_minimum_required(VERSION 3.15)

set(CI_PROJECT_NAME "CellsInterlinkedClient")
set(CI_CLIENT_VERSION 1.0.0)


project(${CI_PROJECT_NAME}
        VERSION ${CI_CLIENT_VERSION})

set(CMAKE_CXX_STANDARD 20)

set(CI_CLIENT_CONAN_CMAKE_FILE ${CI_CLIENT_OUTPUT_DIR}/conanbuildinfo.cmake)
#if(EXISTS ${CI_CLIENT_CONAN_CMAKE_FILE})
#    include(${CI_CLIENT_CONAN_CMAKE_FILE})
#    conan_basic_setup()
#else()
#    message(WARNING "The file ${CI_CLIENT_CONAN_CMAKE_FILE} doesn't exist, you have to run conan install first")
#endif()


# Download automatically, you can also just copy the conan.cmake file
if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
else ()
    message(STATUS "Not downloading conan.cmake, already exists")
endif ()

include(${CMAKE_CURRENT_BINARY_DIR}/conan.cmake)
conan_cmake_run(
        CONANFILE conanfile.txt
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)

file(GLOB_RECURSE CI_CLIENT_SRCFILES
        "*.h"
        "*.cpp")

add_executable(CellsInterlinkedClient ${CI_CLIENT_SRCFILES})
conan_target_link_libraries(CellsInterlinkedClient PUBLIC ${CONAN_LIBS})

configure_file(template/meta/BuildInfo.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/generated/meta/BuildInfo.h)
target_include_directories(CellsInterlinkedClient PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/generated/)
