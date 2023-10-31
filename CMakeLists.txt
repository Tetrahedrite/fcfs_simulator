cmake_minimum_required(VERSION 2.8.12)

project(fcfs_sim)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu11")

set(SOURCE_FILES main.c list.c)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(fcfs_sim ${SOURCE_FILES})
