//
// Created by satya on 23-07-2025.
//

#ifndef IDASTAR_SOLVER_H
#define IDASTAR_SOLVER_H

#include "../Rubiks_Cube_Models/rubiksCube.h"
#include "../PatternDatabases/CornerPatternDatabase.h"

template<typename M,typename H>
class IDAStar_Solver {
private:
    vector<RubiksCube::move> solution;
    unordered_map<M, bool, H> visited ;
    unordered_map<M, RubiksCube::move, H> parent ;
    CornerPatternDatabase cornerDB;

    struct Node {
        M cube ;
        int depth; // value of g(n)
        int h ; // value of estimate (heuristic)

        Node(M _cube, int _depth, int _h) {
            cube = _cube ;
            depth = _depth ;
            h = _h ;
        }

    };


    struct compareCube {
        bool operator()(Node &n1 , Node &n2){
            // Give answer to Q : Is n1 less preffered then n2 ? return true if ans is yes.
            // if this returns true then n2 will come first(at top)
            // if this returns false then n1 will come first(at top)
            if (n1.depth + n1.h > n2.depth + n2.h) return true;
            else if (n1.depth + n1.h == n2.depth + n2.h) return n1.h > n2.h ;
            else return false;
        }
    };

    void resetStructure() {
        solution.clear();
        parent.clear();
        visited.clear();
    }

    pair<M,int> AStar(M & rCube, int bound) {
        priority_queue<Node, vector<Node>, compareCube> pq;
        pq.push(Node(rCube,0, cornerDB.getNumMoves(rCube)));
        int next_bound = 100 ;
        int pushed_node_cnt = 1 ;

        while (!pq.empty()) {
            Node node = pq.top();
            pq.pop();

            if (visited[node.cube]) continue;
            else visited[node.cube] = true ;

            if (node.cube.isSolved()) return {node.cube,bound};
            // Explore moves
            node.depth++ ; // increase depth for upcoming states, nodes
            for (int m = 0 ; m < 18 ; m++) {
                // cout<<"Value of m in loop : "<<m<<endl;
                auto curr_move = RubiksCube::move(m) ;
                node.cube.make_move(curr_move);

                if (!visited[node.cube]) {
                    node.h = cornerDB.getNumMoves(node.cube);
                    int f = node.depth + node.h ;
                    // cout<<bound<<" (<- bound , f ->) "<<f<<endl;
                    if (f <= bound) {
                        // cout<<"PUSHED NODE CNT :"<<++pushed_node_cnt<<endl;
                        // cout<<"Heuristic: "<<node.h<<endl;
                        pq.push(node) ;
                        parent[node.cube] = curr_move;
                    }
                    else {
                        next_bound = min(next_bound, f) ;
                    }
                }

                node.cube.invert_move(curr_move) ;
            }
        }
        // cout<<"END1"<<endl;
        return {rCube,next_bound};
    }

public:

    M rCube ;

    IDAStar_Solver(M _rCube, string const &fileName) {
        rCube = _rCube ;
        cornerDB.fromFile(fileName);
    }

    vector<RubiksCube::move> solve() {
        // int bound = cornerDB.getNumMoves(rCube) ;
        int bound = 1 ;
        auto p = AStar(rCube,bound);
        while (p.second != bound) {
            resetStructure();
            bound = p.second;
            p = AStar(rCube,bound);
        }
        M solved_cube = p.first;
        if (!solved_cube.isSolved()) return {} ;
        M curr_cube = solved_cube ;
        while (curr_cube!=rCube) {
            RubiksCube::move curr_move = parent[curr_cube] ;
            solution.push_back(curr_move);
            curr_cube.invert_move(curr_move);
        }
        reverse(solution.begin(), solution.end());
        rCube = solved_cube ;
        return solution ;
    }

};

#endif //IDASTAR_SOLVER_H
