cmake_minimum_required(VERSION 3.14)

project(
    "ecs"
    DESCRIPTION ""
    HOMEPAGE_URL ""
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(${PROJECT_NAME} INTERFACE cpputils)

