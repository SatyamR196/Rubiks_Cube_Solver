#include<bits/stdc++.h>
#include "Rubiks_Cube_Models/rubiksCube.h"
#include "Rubiks_Cube_Models/_3dArray.cpp"
#include "Rubiks_Cube_Models/_1dArray.cpp"
#include "Rubiks_Cube_Models/_bitBoard.cpp"
#include "Rubiks_Cube_Solvers/DFS_Solver.h"
using namespace std;

signed main() {
    cout<<"Hello People !"<<endl;
    //----------------------------DFS Solver + 3d Arr model---------------------------------------
    // RubiksCube3dArray cube;
    // RubiksCube1dArray cube;
    RubiksCubebitBoard cube;

    cube.print();

    // cube.make_move(RubiksCube::U) ;
    // cube.print();
    // cube.invert_move((RubiksCube::U));
    // cube.make_move(RubiksCube::R) ;
    // cube.print();

    // vector<RubiksCube::move> shuffle_moves = cube.randomShuffle(6);
    vector<RubiksCube::move> shuffle_moves = {RubiksCube::BPRIME, RubiksCube::D2,
    RubiksCube::U2, RubiksCube::D, RubiksCube::RPRIME, RubiksCube::D  } ;
    cube.make_move(RubiksCube::BPRIME) ;
    cube.make_move(RubiksCube::D2) ;
    cube.make_move(RubiksCube::U2) ;
    cube.make_move(RubiksCube::D) ;
    cube.make_move(RubiksCube::RPRIME) ;
    cube.make_move(RubiksCube::D) ;
    cout<<"Random Shuffle Moves: "<<endl;
    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
    cout << "\n";
    cube.print();

    // DFS_Solver<RubiksCube3dArray, Hash3dArray> dfsSolver(cube, 6);
    // DFS_Solver<RubiksCube1dArray, Hash1dArray> dfsSolver(cube, 6);
    DFS_Solver<RubiksCubebitBoard, HashbitBoard> dfsSolver(cube, 6);

    auto start = chrono::high_resolution_clock::now();
    vector<RubiksCube::move> solve_moves = dfsSolver.solve();
    // vector<RubiksCube::move> solve_moves = dfsSolver.solve_rand();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    cout << "DFS Solve Time: " << duration.count() << " ms" << endl;
    cout<<"Solution Moves: "<<endl;
    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
    cout << "\n";
    cout<<"Is it solved : "<<dfsSolver.rCube.isSolved()<<endl;
    dfsSolver.rCube.print();

}