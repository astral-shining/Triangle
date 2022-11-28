cmake_minimum_required(VERSION 3.14)

project(
    "gezzy"
    DESCRIPTION ""
    HOMEPAGE_URL ""
)

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
link_libraries(OpenGL::GL)

add_subdirectory(lib/cpputils)
add_subdirectory(lib/glabs)
add_subdirectory(lib/ecs)
add_subdirectory(lib/glad)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(BUILD_SHARED_LIBS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(lib/glfw)

add_subdirectory(lib/glm)

add_subdirectory(src)

add_library(${PROJECT_NAME} STATIC ${GEZZY_SOURCES})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glm::glm cpputils::cpputils glad::glad glabs::glabs ecs::ecs)
