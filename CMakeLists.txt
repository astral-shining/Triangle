cmake_minimum_required(VERSION 3.14)

# set the project name
project(triangle VERSION 0.1)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
message(${CMAKE_BUILD_TYPE})


#set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-Wall -pedantic -Werror -Wno-format-security")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Og -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffunction-sections -fdata-sections -fno-rtti -fvisibility=hidden -DNDEBUG")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_EXE_LINKER_FLAGS "-s -flto -Wl,--gc-sections -Wl,--strip-all")
endif()

include_directories(${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(gezzy)
link_libraries(gezzy)

add_subdirectory(src)

add_library(${CMAKE_PROJECT_NAME}_obj OBJECT ${TRIANGLE_SOURCES})

# add the executable
add_executable(${CMAKE_PROJECT_NAME} $<TARGET_OBJECTS:gezzy> $<TARGET_OBJECTS:${CMAKE_PROJECT_NAME}_obj>)
