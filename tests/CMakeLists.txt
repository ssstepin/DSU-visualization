cmake_minimum_required(VERSION 3.25)
project(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("../dsu", "./headers", "./sources")

add_executable(tests main.cpp tests.cpp test_light.cpp)
