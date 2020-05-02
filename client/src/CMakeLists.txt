cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} ClientMain.cpp ${CI_SRC_FILES_NO_MAIN})
target_include_directories(${PROJECT_NAME} PRIVATE ${CI_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})