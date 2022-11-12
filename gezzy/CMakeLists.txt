cmake_minimum_required(VERSION 3.14)

project(
    "gezzy"
    DESCRIPTION ""
    HOMEPAGE_URL ""
)

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
link_libraries(OpenGL::GL)

find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(glfw)

add_subdirectory(cpputils)
link_libraries(cpputils)
add_subdirectory(glabs)
link_libraries(glabs)
add_subdirectory(ecs)
link_libraries(ecs)

add_subdirectory(glad)
add_subdirectory(gezzy)

add_library(${PROJECT_NAME} STATIC ${GEZZY_SOURCES})
add_library(gezzy::gezzy ALIAS gezzy)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
