#include<bits/stdc++.h>
#include "Rubiks_Cube_Models/rubiksCube.h"
#include "Rubiks_Cube_Models/_3dArray.cpp"
#include "Rubiks_Cube_Solvers/DFS_Solver.h"
using namespace std;

signed main() {
    cout<<"Hello People !"<<endl;
    //-----------------------------------DFS Solver---------------------------------------
    RubiksCube3dArray cube;
    cube.print();
    // cube.make_move(RubiksCube::DPRIME) ;
    // cube.print();
    // cube.invert_move((RubiksCube::DPRIME));
    // cube.make_move(RubiksCube::R) ;
    // cube.print();
    vector<RubiksCube::move> shuffle_moves = cube.randomShuffle(7);
    cout<<"Random Shuffle Moves: "<<endl;
    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
    cout << "\n";
    cube.print();

    DFS_Solver<RubiksCube3dArray, Hash3dArray> dfsSolver(cube, 8);
    auto start = chrono::high_resolution_clock::now();
    vector<RubiksCube::move> solve_moves = dfsSolver.solve();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "DFS Solve Time: " << duration.count() << " ms" << endl;
    // vector<RubiksCube::move> solve_moves = dfsSolver.solve_rand();
    cout<<"Solution Moves: "<<endl;
    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
    cout << "\n";
    cout<<"Is it solved : "<<dfsSolver.rCube.isSolved()<<endl;
    dfsSolver.rCube.print();
}