cmake_minimum_required(VERSION 3.10)
project(mai_oop_lab_04)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${CMAKE_PROJECT_NAME}_lib INTERFACE
    ./include/figure.h
    ./include/square.h
    ./include/rectangle.h
    ./include/trapezoid.h
    ./include/array.h
)

add_executable(${CMAKE_PROJECT_NAME}_out main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}_out PRIVATE ${CMAKE_PROJECT_NAME}_lib)

enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests tests/test.cpp)
target_link_libraries(tests ${CMAKE_PROJECT_NAME}_lib gtest_main)

add_test(NAME ${CMAKE_PROJECT_NAME}Tests COMMAND tests)