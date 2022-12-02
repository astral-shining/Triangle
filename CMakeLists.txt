cmake_minimum_required(VERSION 3.14)

# set the project name
project(triangle VERSION 0.1)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
message(${CMAKE_BUILD_TYPE})

#set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-Wall -pedantic -Werror -Wno-format-security")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Og")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffunction-sections -fdata-sections -fno-rtti -fvisibility=hidden -DNDEBUG")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_EXE_LINKER_FLAGS "-s -flto -Wl,--gc-sections -Wl,--strip-all")
endif()

if (UNIX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
elseif(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -fstack-protector")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(lib/gezzy)

file(GLOB_RECURSE TRIANGLE_SOURCES src/*.cpp)

# add the executable
add_executable(${CMAKE_PROJECT_NAME} ${TRIANGLE_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE gezzy::gezzy)
