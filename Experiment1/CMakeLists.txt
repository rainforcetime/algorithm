cmake_minimum_required(VERSION 3.24)
project(Experiment1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Experiment1 main.cpp
        generatePoints.cpp
        generatePoints.h
        force.cpp)
