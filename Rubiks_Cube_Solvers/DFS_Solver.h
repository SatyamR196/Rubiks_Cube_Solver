//
// Created by satya on 19-07-2025.
//

#ifndef DFS_SOLVER_H
#define DFS_SOLVER_H

#include "../Rubiks_Cube_Models/rubiksCube.h"

// Typename M for models, so T = 3dArray / 1dArray / Bitboard model
// Typename H for corresponding hash fxn, so H = Hash3d / Hash1d / HashBB

template<typename M, typename H>
class DFS_Solver {
private:
    vector<RubiksCube::move> solution;
    size_t max_depth;

    bool dfs(M &rCube,size_t depth) {
        if (rCube.isSolved()) return true;
        if (depth > max_depth) return false;

        // explore edges(18 basic moves) using plain loop from [0-17]
        for (int m =0 ; m<18 ; m++) {
            rCube.make_move(RubiksCube::move(m)) ;
            solution.push_back(RubiksCube::move(m)) ;
            if (dfs(rCube,depth+1)) return true ;
            solution.pop_back() ;
            rCube.invert_move(RubiksCube::move(m)) ;
        }
        return false;
    }

    bool dfs_rand(M &rCube,size_t depth) {
        if (rCube.isSolved()) return true;
        if (depth > max_depth) return false;

        // explore edges(18 basic moves) choosing any random move between [0-17]
        for (int m =0 ; m<18 ; m++) {
            rCube.make_move(RubiksCube::move(RubiksCube::getRandInt(0,17))) ;
            solution.push_back(RubiksCube::move(m)) ;
            if (dfs(rCube,depth+1)) return true ;
            solution.pop_back() ;
            rCube.invert_move(RubiksCube::move(m)) ;
        }
        return false;
    }

public:
    M rCube;
    explicit DFS_Solver(M _rCube, size_t _max_depth=6) {
        rCube = _rCube ;
        max_depth = _max_depth ;
    }

    vector<RubiksCube::move> solve() {
        dfs(rCube,1) ;
        return solution ;
    }

    vector<RubiksCube::move> solve_rand() {
        dfs_rand(rCube,1) ;
        return solution ;
    }

};



#endif //DFS_SOLVER_H

