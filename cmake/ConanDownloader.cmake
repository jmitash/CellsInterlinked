# Download automatically, you can also just copy the conan.cmake file
if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
else ()
    message(STATUS "Not downloading conan.cmake, already exists")
endif ()