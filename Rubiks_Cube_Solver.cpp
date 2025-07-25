#include<bits/stdc++.h>
#include "Rubiks_Cube_Models/rubiksCube.h"
#include "Rubiks_Cube_Models/_3dArray.cpp"
#include "Rubiks_Cube_Models/_1dArray.cpp"
#include "Rubiks_Cube_Models/_bitBoard.cpp"
#include "Rubiks_Cube_Solvers/DFS_Solver.h"
#include "Rubiks_Cube_Solvers/ID_DFS_Solver.h"
#include "Rubiks_Cube_Solvers/BFS_Solver.h"
#include "Rubiks_Cube_Solvers/IDAStar_Solver.h"
using namespace std;

signed main() {
    cout<<"Hello People !"<<endl;
    // ----------------------- Code to create Corner Database ---------------------
    // Run it only once.
    // CornerDBMaker dbMaker(fileName, 0x99);
    // dbMaker.bfsAndStore();
    // ----------------------Check : CornerPatternDatabase ---------------------------------------------

    string fileName = "D:\\C++ DSA\\Delta\\Projects\\Rubix_Cube_Solver\\PatternDatabases\\heuristic_data.txt";
    // CornerPatternDatabase cornerDB;
    // cout<<"READ : "<<cornerDB.fromFile(fileName)<<endl ;

    // RubiksCubebitBoard cube;
    // cube.print();

    // cout << (int)cornerDB.getNumMoves(cube) << "\n";

    // cornerDB.setNumMoves(cube, 5);

    // cout << (int)cornerDB.getNumMoves(cube) << "\n";

    // cube.randomShuffle(2);
    // cube.print();
    // cout << (int)cornerDB.getNumMoves(cube) << "\n";

    // cornerDB.setNumMoves(cube, 6);

    // cout << (int)cornerDB.getNumMoves(cube) << "\n";

    //----------------------------All Solver + all cube model---------------------------------------

    // CHOOSE YOUR MODEL :-
    // RubiksCube3dArray cube;
    // RubiksCube1dArray cube;
    RubiksCubebitBoard cube;

    cube.print();

    // RANDOMLY SHUFFLE CUBE TO simulate jumbled state :-
    vector<RubiksCube::move> shuffle_moves = cube.randomShuffle(13);

    // vector<RubiksCube::move> shuffle_moves = {RubiksCube::BPRIME, RubiksCube::D2,
    // RubiksCube::U2, RubiksCube::D, RubiksCube::RPRIME, RubiksCube::D  } ;
    // cube.make_move(RubiksCube::BPRIME) ;
    // cube.make_move(RubiksCube::D2) ;
    // cube.make_move(RubiksCube::U2) ;
    // cube.make_move(RubiksCube::D) ;
    // cube.make_move(RubiksCube::RPRIME) ;
    // cube.make_move(RubiksCube::D) ;

    cout<<"Random Shuffle Moves: "<<endl;
    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
    cout << "\n";
    cube.print();

    // CHOOSE THE TYPE OF SOLVER :-
    // DFS_Solver<RubiksCube3dArray, Hash3dArray> dfsSolver(cube, 6);
    // DFS_Solver<RubiksCube1dArray, Hash1dArray> dfsSolver(cube, 6);
    // DFS_Solver<RubiksCubebitBoard, HashbitBoard> dfsSolver(cube, 6);
    // ID_DFS_Solver<RubiksCubebitBoard, HashbitBoard> dfsSolver(cube, 6);
    // BFS_Solver<RubiksCubebitBoard, HashbitBoard> Solver(cube);
    IDAStar_Solver<RubiksCubebitBoard, HashbitBoard> Solver(cube,fileName);

    auto start = chrono::high_resolution_clock::now();
    vector<RubiksCube::move> solve_moves = Solver.solve();
    // vector<RubiksCube::move> solve_moves = Solver.solve_rand();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    cout << "Solve Time: " << duration.count() << " ms" << endl;
    cout<<"Solution Moves: "<<endl;
    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
    cout << "\n";
    cout<<"Is it solved : "<<Solver.rCube.isSolved()<<endl;
    Solver.rCube.print();

}