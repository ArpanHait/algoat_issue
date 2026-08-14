cmake_minimum_required(VERSION 3.15)
project(test_package CXX)

find_package(algoat REQUIRED)

add_executable(test_package src/example.cpp)
target_link_libraries(test_package PRIVATE algoat::algoat)
