cmake_minimum_required(VERSION 3.20)
project(esercitazione8) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla -Wno-sign-compare")

find_package(Eigen3 CONFIG REQUIRED)
list(APPEND libraries_list PUBLIC Eigen3::Eigen)

add_executable(test_gradiente_coniugato test_gradiente_coniugato.cpp)
add_test(NAME test_grad COMMAND test_gradiente_coniugato)
enable_testing()
