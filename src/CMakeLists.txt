cmake_minimum_required(VERSION 3.0)

project(gpstime)

message(=============================================================)
message("-- Ready to compile library")
message(=============================================================)

add_library(${PROJECT_NAME} 
    GPSTime.c
)