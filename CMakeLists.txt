cmake_minimum_required(VERSION 3.0)

project(gpstime VERSION 0.0.1 LANGUAGES C)

set(CMAKE_BUILD_TYPE "Debug")

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(
    inc
)

link_directories(
    src
)

add_subdirectory(src)
add_subdirectory(examples)