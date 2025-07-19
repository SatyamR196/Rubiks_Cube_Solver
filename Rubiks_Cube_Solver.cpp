#include<bits/stdc++.h>
#include "Rubiks_Cube_Models/rubiksCube.h"
#include "Rubiks_Cube_Models/_3dArray.cpp"
#include "Rubiks_Cube_Solvers/DFS_Solver.h"
using namespace std;

signed main() {
    cout<<"Hello World!"<<endl;
    // DFS Solver Testing __________________________________________________________________________________________
    RubiksCube3dArray cube;
    cube.print();
    cube.make_move(RubiksCube::F) ;
    cube.print();

    cube.make_move(RubiksCube::R) ;
    cube.print();
    // vector<RubiksCube::move> shuffle_moves = cube.randomShuffle(1);
    // for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
    cout << "\n";
    // cube.print();

    DFS_Solver<RubiksCube3dArray, Hash3dArray> dfsSolver(cube, 8);
    vector<RubiksCube::move> solve_moves = dfsSolver.solve();

    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
    cout << "\n";
    cout<<dfsSolver.rCube.isSolved()<<endl;
    dfsSolver.rCube.print();
}