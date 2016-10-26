cmake_minimum_required(VERSION 3.5)
project(Regular_Expression_Practice 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp RegularExpressionParser.cc)
add_executable(Regular_Expression_Practice 1 ${SOURCE_FILES})