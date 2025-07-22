//
// Created by satya on 22-07-2025.
//

#ifndef ID_DFS_SOLVER_H
#define ID_DFS_SOLVER_H
#include "../Rubiks_Cube_Models/rubiksCube.h"
#include "DFS_Solver.h"
// Typename M for models, so T = 3dArray / 1dArray / Bitboard model
// Typename H for corresponding hash fxn, so H = Hash3d / Hash1d / HashBB

template<typename M, typename H>
class ID_DFS_Solver {
private:
    vector<RubiksCube::move> solution{};
    size_t max_depth;

public:
    M rCube;
    explicit ID_DFS_Solver(M _rCube, size_t _max_depth=6) {
        rCube = _rCube ;
        max_depth = _max_depth ;
    }

    vector<RubiksCube::move> solve() {
        for (int allowed_depth = 1 ; allowed_depth <= max_depth ; allowed_depth++) {
            DFS_Solver<M,H> dfs_solver(rCube,allowed_depth);
            solution = dfs_solver.solve() ;
            if (dfs_solver.rCube.isSolved()) {
                rCube = dfs_solver.rCube;
                break;
            }
        }
        return solution ;
    }

    vector<RubiksCube::move> solve_rand() {
        for (int allowed_depth = 1 ; allowed_depth <= max_depth ; allowed_depth++) {
            DFS_Solver<M,H> dfs_solver(rCube,allowed_depth);
            solution = dfs_solver.solve_rand() ;
            if (dfs_solver.rCube.isSolved()) {
                rCube = dfs_solver.rCube;
                break;
            }
        }
        return solution ;
    }

};

#endif //ID_DFS_SOLVER_H
