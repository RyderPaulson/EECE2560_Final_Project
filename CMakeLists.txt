cmake_minimum_required(VERSION 3.29)
project(EECE2560_Final_Project)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp)
add_executable(EECE2560_Final_Project ${SOURCE_FILES})

include_directories(Forecaster_lib)
add_subdirectory(Forecaster_lib)

target_link_libraries(EECE2560_Final_Project Forecaster_lib)