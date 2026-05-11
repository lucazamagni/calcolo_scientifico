cmake_minimum_required(VERSION 3.20)
project(esercitazione6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(test_edges_graph test_edges_graph.cpp)
add_test(NAME edges_graph COMMAND test_edges_graph)
enable_testing()