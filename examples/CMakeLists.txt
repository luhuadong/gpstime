cmake_minimum_required(VERSION 3.0)

project(gpstime_demos LANGUAGES CXX)

message(=============================================================)
message("-- Ready to compile demo")
message(=============================================================)

link_directories(
    ${BUILD_DIR}/src
)

add_executable(time-test time-test.cpp)

target_link_libraries(time-test gpstime)