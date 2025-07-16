//
// Created by satya on 15-07-2025.
//

#include "rubiksCube.h"
#include <random>

char RubiksCube::getColorLetter(color c) {
    switch (c) {
        case GREEN: return 'G';
        case BLUE: return 'B';
        case RED: return 'R';
        case YELLOW: return 'Y';
        case WHITE: return 'W';
        case ORANGE: return 'O';
        default: return ' ';
    }
}

string RubiksCube::getMove(move m) {
    switch (m) {
        case L: return "L";
        case LPRIME: return "L'";
        case L2: return "L2";

        case R: return "R";
        case RPRIME: return "R'";
        case R2: return "R2";

        case U: return "U";
        case UPRIME: return "U'";
        case U2: return "U2";

        case D: return "D";
        case DPRIME: return "D'";
        case D2: return "D2";

        case F: return "F";
        case FPRIME: return "F'";
        case F2: return "F2";

        case B: return "B";
        case BPRIME: return "B'";
        case B2: return "B2";

        default: return "UNKNOWN";
    }
}

RubiksCube& RubiksCube::make_move(move m) {
    switch (m) {
        case L : return this->l() ;
        case LPRIME : return this->lPrime() ;
        case L2 : return this->l2() ;

        case R : return this->r() ;
        case RPRIME : return this->rPrime() ;
        case R2 : return this->r2() ;

        case U : return this->u() ;
        case UPRIME : return this->uPrime() ;
        case U2 : return this->u2() ;

        case D : return this->d() ;
        case DPRIME : return this->dPrime() ;
        case D2 : return this->d2() ;

        case F : return this->f() ;
        case FPRIME : return this->fPrime() ;
        case F2 : return this->f2() ;

        case B : return this->b() ;
        case BPRIME : return this->bPrime() ;
        case B2 : return this->b2() ;
    }
}

RubiksCube& RubiksCube::inverse_move(move m) {
    switch (m) {
        case L : return this->lPrime() ;
        case LPRIME : return this->l() ;
        case L2 : return this->l2() ;

        case R : return this->rPrime() ;
        case RPRIME : return this->r() ;
        case R2 : return this->r2() ;

        case U : return this->uPrime() ;
        case UPRIME : return this->u() ;
        case U2 : return this->u2() ;

        case D : return this->dPrime() ;
        case DPRIME : return this->d() ;
        case D2 : return this->d2() ;

        case F : return this->fPrime() ;
        case FPRIME : return this->f() ;
        case F2 : return this->f2() ;

        case B : return this->bPrime() ;
        case BPRIME : return this->b() ;
        case B2 : return this->b2() ;

    }
}

void RubiksCube::print() {
    cout<<"RUBIKS CUBE (Open Layout):"<<endl<<endl;

    // Section 1 (UP Face)
    for (int row= 0 ; row<3 ; row++) {
        for (int i=0; i<9 ; i++) cout<<" ";
        for (int col= 0 ; col<3 ; col++) {
            cout<<getColorLetter(getColor(UP,row,col))<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    // Section 2 (LEFT, FRONT, RIGHT, BACK Faces)
    for (int row= 0 ; row<3 ; row++) {
        for (int col= 0 ; col<3 ; col++) {
            cout<<getColorLetter(getColor(LEFT,row,col))<<" ";
        }
        cout<<"   ";
        for (int col= 0 ; col<3 ; col++) {
            cout<<getColorLetter(getColor(FRONT,row,col))<<" ";
        }
        cout<<"   ";
        for (int col= 0 ; col<3 ; col++) {
            cout<<getColorLetter(getColor(RIGHT,row,col))<<" ";
        }
        cout<<"   ";
        for (int col= 0 ; col<3 ; col++) {
            cout<<getColorLetter(getColor(BACK,row,col))<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    // Section 3 (DOWN Face)
    for (int row= 0 ; row<3 ; row++) {
        for (int i=0; i<9 ; i++) cout<<" ";
        for (int col= 0 ; col<3 ; col++) {
            cout<<getColorLetter(getColor(DOWN,row,col))<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

// Creating generator and distribution (for generating random nums)
random_device rd;  // Seed (non-deterministic)
mt19937 gen(rd()); // Mersenne Twister engine
uniform_int_distribution<> dist(0, 17); // range [0, 17]

vector<RubiksCube::move> RubiksCube::randomShuffle(unsigned x) {
    vector<move> steps ;
    for (unsigned i = 0 ; i < x ; i++) {
        unsigned moveIndex = dist(gen)%18 ;
        move m = static_cast<move>(moveIndex) ;
        steps.push_back(m) ;
        this->make_move(m) ;
    }
    return steps;
}

// get the colors of corner cubie
string getCornerColorString(unsigned ind){

};

unsigned getCornerIndex(unsigned ind) {

};

unsigned getCornerOrientation(unsigned ind) {

};

