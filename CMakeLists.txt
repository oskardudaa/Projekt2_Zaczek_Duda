cmake_minimum_required(VERSION 3.10)
project(STLAssignment)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/main.cpp
)

set(TEST_SOURCES
    tests/test_main.cpp
)

add_executable(stl_main ${SOURCES})

add_executable(stl_tests ${TEST_SOURCES})