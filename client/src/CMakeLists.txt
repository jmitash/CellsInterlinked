cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} ClientMain.cpp)
target_link_libraries(${PROJECT_NAME} ${CI_PROJECT_LIB_NAME})