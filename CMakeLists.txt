cmake_minimum_required(VERSION 3.29)
project(EECE2560_Final_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(EECE2560_Final_Project main.cpp
        Market.cpp
        Market.h
        Algorithm.cpp
        Algorithm.h
)

#[[
find_package(PythonLibs 2.7)
target_include_directories(EECE2560_Final_Project PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(EECE2560_Final_Project ${PYTHON_LIBRARIES})
]]