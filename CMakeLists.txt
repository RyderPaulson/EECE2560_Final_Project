cmake_minimum_required(VERSION 3.29)
project(EECE2560_Final_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(EECE2560_Final_Project main.cpp
        lib/Market.cpp
        lib/Market.h
        lib/Algorithm.cpp
        lib/Algorithm.h
        lib/io.cpp
        lib/io.h
)