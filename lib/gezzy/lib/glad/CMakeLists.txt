cmake_minimum_required(VERSION 3.14)

project(
    "glad"
    DESCRIPTION ""
    HOMEPAGE_URL ""
)

add_library(${PROJECT_NAME} OBJECT src/glad.cpp)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC include)
