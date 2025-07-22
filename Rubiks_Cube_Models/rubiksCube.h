//
// Created by satya on 15-07-2025.
//

#ifndef RUBIKSCUBE_H
#define RUBIKSCUBE_H

#include "bits/stdc++.h"
using namespace std;

// This will be the base abstract class for all the models of Rubik's cube
// we are going to create, variable like face color, Faces and Fxn like
// print(), which are common to all the models will be defined and implemented here itself.
// But the fxn like getColor(cubie), 18 basic moves, isSolved() will be defined as pure
// virtual fxn here and must be implemented in the derived model class.

class RubiksCube {
    public:
    virtual ~RubiksCube() = default;

    enum face {
        UP = 0,
        LEFT = 1,
        FRONT = 2,
        RIGHT = 3,
        BACK = 4,
        DOWN = 5,
        // Even if we don't explicitly assign values to these, C++ will automatically
        // assign integer values starting from 0, increasing by 1 for each following item.
    };

    enum color {
        WHITE = 0,
        GREEN = 1,
        RED = 2,
        BLUE = 3,
        ORANGE = 4,
        YELLOW = 5
        // Rubik's cube of 3x3x3 has 6 faces each having a different color.
    };

    enum move {
        L, LPRIME, L2, // 3 Moves of left face
        R, RPRIME, R2, // 3 Moves of right face
        U, UPRIME, U2, // 3 Moves of up face
        D, DPRIME, D2, // 3 Moves of down face
        F, FPRIME, F2, // 3 Moves of front face
        B, BPRIME, B2, // 3 Moves of back face
        // There are a total of 18 basic moves in cube
    };

    enum move_type { // where M is any general move, M=L, or M=R...
        M1,
        M2,
        MPRIME,
    };

    // getColor fxn defined below will return the color of mini-square in a given face
    virtual color getColor(face F, unsigned row, unsigned col) const = 0 ;

    // getColorLetter static member fxn, if color is "GREEN" returns "G" and so on
    static char getColorLetter(const color c) ;
    // getMove return the move in string format, if move==L2, return "L2"
    static string getMove(move m) ;

    // isSolved(curr_state of cube) will return true if cube is in solved state else false.
    virtual bool isSolved() const = 0;

    // This will print the cube as if it is opened, e.g.
    /*
    Sides wise after opening :
         U
       L F R B
         D

    Color wise:

               W W W
               W W W
               W W W

       G G G   R R R   B B B   O O O
       G G G   R R R   B B B   O O O
       G G G   R R R   B B B   O O O

               Y Y Y
               Y Y Y
               Y Y Y
     */

    // will be implemented in .cpp file
    void print() const;

    //will be implemented in .cpp file
    static int getRandInt(int min,int max) ;
    // Fxn randomShuffle(x) : return a vector of moves made to jumble the cube
    // from solved state using x random moves
    vector<move> randomShuffle(unsigned x) ;

    // Perform a move on rubix cube, return reference to the same object.
    RubiksCube& make_move(move m) ;

    // This will help us make all 18 basic moves in a generalised way
    // Note : adjecent faces must be given in CW order if face F is at top
    // virtual RubiksCube& move_helper(face F, vector<face>adj_face, move_type MT) = 0;

    // This function applies the inverse of the given move
    // invert(L) would apply L'
    //invert (R2) would apply R2(since its own inverse is itself)
    //invert (U') would apply U
    RubiksCube& invert_move(move m) ;

    // Each fxn will simulate one of the 18 basic moves.
    virtual RubiksCube &f() = 0;
    virtual RubiksCube &fPrime() = 0;
    virtual RubiksCube &f2() = 0;

    virtual RubiksCube &u() = 0;
    virtual RubiksCube &uPrime() = 0;
    virtual RubiksCube &u2() = 0;

    virtual RubiksCube &l() = 0;
    virtual RubiksCube &lPrime() = 0;
    virtual RubiksCube &l2() = 0;

    virtual RubiksCube &r() = 0;
    virtual RubiksCube &rPrime() = 0;
    virtual RubiksCube &r2() = 0;

    virtual RubiksCube &d() = 0;
    virtual RubiksCube &dPrime() = 0;
    virtual RubiksCube &d2() = 0;

    virtual RubiksCube &b() = 0;
    virtual RubiksCube &bPrime() = 0;
    virtual RubiksCube &b2() = 0;

    // get the colors of corner cubie
    string getCornerColorString(unsigned ind) const;

    unsigned getCornerIndex(unsigned ind) const;

    unsigned getCornerOrientation(unsigned ind) const;
};

#endif //RUBIKSCUBE_H
