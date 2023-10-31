cmake_minimum_required(VERSION 3.20)
project(compiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(.)

add_executable(compiler "lex.yy.cpp"
        unistd.h
        classes_functions.cpp
        classesnodes.h)
