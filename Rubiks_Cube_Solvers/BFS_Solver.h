//
// Created by satya on 22-07-2025.
//

#ifndef BFS_SOLVER_H
#define BFS_SOLVER_H

#include "../Rubiks_Cube_Models/rubiksCube.h"

template<typename M, typename H>
class BFS_Solver {
private:
    vector<RubiksCube::move> solution;
    unordered_map<M,bool,H> visited ;
    unordered_map<M, RubiksCube::move,H> parent ;

    M bfs(M &rCube) {
        queue<M> q ;
        q.push(rCube) ;
        visited[rCube] = true ;

        while (!q.empty()) {
            M rk = q.front() ;
            q.pop() ;

            if (rk.isSolved()) return rk ;

            for (int m = 0 ; m < 18 ; m++) {
                auto  curr_move = RubiksCube::move(m) ;
                rk.make_move(curr_move) ;
                if (!visited[rk]) {
                    q.push(rk) ;
                    visited[rk] = true ;
                    parent[rk] = curr_move ;
                }
                rk.invert_move(curr_move) ;
            }

        }
        return rCube ;
    }

public:
    M rCube ;
    explicit  BFS_Solver(M _rCube) {
        rCube = _rCube ;
    }

    // Do BFS on given state of rubik's cube and retrive the solution moves using parent(back-pointer)
    vector<RubiksCube::move> solve() {
        M solved_cube = bfs(rCube) ;
        // assert(solved_cube.isSolved());
        if (!solved_cube.isSolved()) { return {} ;} ;

        M curr_cube = solved_cube;

        while (!(curr_cube == rCube)) {
            auto move_made = parent[curr_cube] ;
            solution.push_back(move_made);
            curr_cube.invert_move(move_made) ;
        }

        rCube = solved_cube ;
        reverse(solution.begin(), solution.end()) ;
        return solution ;

    }

};

#endif //BFS_SOLVER_H
