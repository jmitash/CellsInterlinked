project(${CI_PROJECT_NAME} VERSION ${CI_PROJECT_VERSION})
add_executable(${CI_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

message(VERBOSE "Using ${CMAKE_CURRENT_BINARY_DIR} as ${CI_PROJECT_FRIENDLY_NAME} binary directory")

# Download, run, and link Conan
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ConanDownloader.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/conan.cmake)
conan_cmake_run(
        CONANFILE conanfile.txt
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)
conan_target_link_libraries(${CI_PROJECT_NAME} PUBLIC ${CONAN_LIBS})

# Discover and include source files
file(GLOB_RECURSE CI_PROJECT_SRCFILES CONFIGURE_DEPENDS "*.h" "*.cpp" "../common/**/*.h" "../common/**/*.cpp")
target_sources(${CI_PROJECT_NAME} PRIVATE ${CI_PROJECT_SRCFILES})

# Discover, configure, and include template files
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ConfigureTemplateFiles.cmake)
configure_template_files()
target_include_directories(${CI_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/generated/)