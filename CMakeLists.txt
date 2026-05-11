cmake_minimum_required(VERSION 3.10)

project(snake_game LANGUAGES CXX)

file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include/
)

