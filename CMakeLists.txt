cmake_minimum_required(VERSION 3.31)
project(Rubix_Cube_Solver)

set(CMAKE_CXX_STANDARD 23)

add_executable(Rubix_Cube_Solver main.cpp
        Rubiks_Cube_Models/rubiksCube.cpp
        Rubiks_Cube_Models/rubiksCube.h)
