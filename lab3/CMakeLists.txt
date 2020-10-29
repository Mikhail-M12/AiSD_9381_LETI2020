cmake_minimum_required(VERSION 3.17)
project(lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab3
        Test/input.txt
        lab3.cpp
        Test/output.txt Test/Test.cpp Test/Test.h lab3.h)
