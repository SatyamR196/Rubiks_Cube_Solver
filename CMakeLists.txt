cmake_minimum_required(VERSION 3.31)
project(Rubix_Cube_Solver)

set(CMAKE_CXX_STANDARD 23)

add_executable(Rubix_Cube_Solver Rubiks_Cube_Solver.cpp
        Rubiks_Cube_Models/rubiksCube.cpp
        Rubiks_Cube_Models/rubiksCube.h
        Rubiks_Cube_Models/_3DArray.cpp
        Rubiks_Cube_Solvers/DFS_Solver.h
        Rubiks_Cube_Models/_1dArray.cpp
        Rubiks_Cube_Models/_bitBoard.cpp
        Rubiks_Cube_Solvers/ID_DFS_Solver.h
)
