cmake_minimum_required(VERSION 3.25)
project(tests)

set(CMAKE_CXX_STANDARD 17)

include_directories("../dsu", "./headers", "./sources")

add_executable(tests main.cpp sources/tests.cpp sources/test_light.cpp)
