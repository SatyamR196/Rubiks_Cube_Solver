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
    //create random num generator
    mt19937 g{random_device{}()};

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

        vector<RubiksCube::move> all_moves = {
            RubiksCube::U, RubiksCube::U2, RubiksCube::UPRIME,
            RubiksCube::L, RubiksCube::L2, RubiksCube::LPRIME,
            RubiksCube::F,RubiksCube::F2,RubiksCube::FPRIME,
            RubiksCube::D,RubiksCube::D2,RubiksCube::DPRIME,
            RubiksCube::R,RubiksCube::R2,RubiksCube::RPRIME,
            RubiksCube::B,RubiksCube::B2,RubiksCube::BPRIME
        } ;

        // Shuffle the moves in the arr
        std::shuffle(all_moves.begin(), all_moves.end(), g);

        // explore edges(18 basic moves) choosing any random move between [0-17]
        for (auto mv : all_moves) {
            rCube.make_move(mv);
            solution.push_back(mv);
            if (dfs(rCube,depth+1)) return true ;
            solution.pop_back() ;
            rCube.invert_move(mv) ;
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
        solution.clear();
        dfs(rCube,1) ;
        return solution ;
    }

    vector<RubiksCube::move> solve_rand() {
        solution.clear();
        dfs_rand(rCube,1) ;
        return solution ;
    }

};



#endif //DFS_SOLVER_H

