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

// RubiksCube& RubiksCube::make_move(move m) {
//     switch (m) {
//         case L : return this->l() ;
//         case LPRIME : return this->lPrime() ;
//         case L2 : return this->l2() ;
//
//         case R : return this->r() ;
//         case RPRIME : return this->rPrime() ;
//         case R2 : return this->r2() ;
//
//         case U : return this->u() ;
//         case UPRIME : return this->uPrime() ;
//         case U2 : return this->u2() ;
//
//         case D : return this->d() ;
//         case DPRIME : return this->dPrime() ;
//         case D2 : return this->d2() ;
//
//         case F : return this->f() ;
//         case FPRIME : return this->fPrime() ;
//         case F2 : return this->f2() ;
//
//         case B : return this->b() ;
//         case BPRIME : return this->bPrime() ;
//         case B2 : return this->b2() ;
//     }
// }

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

RubiksCube& RubiksCube::invert_move(move m) {
    switch (m) {
        case L : return this->make_move(LPRIME) ;
        case LPRIME : return this->make_move(L) ;
        case L2 : return this->make_move(L2) ;

        case R : return this->make_move(RPRIME) ;
        case RPRIME : return this->make_move(R) ;
        case R2 : return this->make_move(R2) ;

        case U : return this->make_move(UPRIME) ;
        case UPRIME : return this->make_move(U) ;
        case U2 : return this->make_move(U2) ;

        case D : return this->make_move(DPRIME) ;
        case DPRIME : return this->make_move(D) ;
        case D2 : return this->make_move(D2) ;

        case F : return this->make_move(FPRIME) ;
        case FPRIME : return this->make_move(F) ;
        case F2 : return this->make_move(F2) ;

        case B : return this->make_move(BPRIME) ;
        case BPRIME : return this->make_move(B) ;
        case B2 : return this->make_move(B2) ;

    }
}

void RubiksCube::print() const{
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

int RubiksCube::getRandInt(int min,int max) {
    // Creating generator and distribution (for generating random nums)
    random_device rd;  // Seed (non-deterministic)
    mt19937 gen(rd()); // Mersenne Twister engine
    uniform_int_distribution<> dist(0, 17); // range [0, 17]
    return dist(gen);
}

vector<RubiksCube::move> RubiksCube::randomShuffle(unsigned x) {
    vector<move> steps ;
    for (unsigned i = 0 ; i < x ; i++) {
        unsigned moveIndex = getRandInt(0,17) ;
        move m = static_cast<move>(moveIndex) ;
        steps.push_back(m) ;
        this->make_move(m) ;
    }
    return steps;
}

// get the colors of corner cubie
string RubiksCube::getCornerColorString(uint8_t ind) const {
    string str = "";

    switch (ind) {
//        UFR
        case 0:
            str += getColorLetter(getColor(face::UP, 2, 2));
            str += getColorLetter(getColor(face::FRONT, 0, 2));
            str += getColorLetter(getColor(face::RIGHT, 0, 0));
            break;

//            UFL
        case 1:
            str += getColorLetter(getColor(face::UP, 2, 0));
            str += getColorLetter(getColor(face::FRONT, 0, 0));
            str += getColorLetter(getColor(face::LEFT, 0, 2));
            break;

//            UBL
        case 2:
            str += getColorLetter(getColor(face::UP, 0, 0));
            str += getColorLetter(getColor(face::BACK, 0, 2));
            str += getColorLetter(getColor(face::LEFT, 0, 0));
            break;

//            UBR
        case 3:
            str += getColorLetter(getColor(face::UP, 0, 2));
            str += getColorLetter(getColor(face::BACK, 0, 0));
            str += getColorLetter(getColor(face::RIGHT, 0, 2));
            break;

//            DFR
        case 4:
            str += getColorLetter(getColor(face::DOWN, 0, 2));
            str += getColorLetter(getColor(face::FRONT, 2, 2));
            str += getColorLetter(getColor(face::RIGHT, 2, 0));
            break;

//            DFL
        case 5:
            str += getColorLetter(getColor(face::DOWN, 0, 0));
            str += getColorLetter(getColor(face::FRONT, 2, 0));
            str += getColorLetter(getColor(face::LEFT, 2, 2));
            break;

//            DBR
        case 6:
            str += getColorLetter(getColor(face::DOWN, 2, 2));
            str += getColorLetter(getColor(face::BACK, 2, 0));
            str += getColorLetter(getColor(face::RIGHT, 2, 2));
            break;

//            DBL
        case 7:
            str += getColorLetter(getColor(face::DOWN, 2, 0));
            str += getColorLetter(getColor(face::BACK, 2, 2));
            str += getColorLetter(getColor(face::LEFT, 2, 0));
            break;
    }
    return str;
}

uint8_t RubiksCube::getCornerIndex(uint8_t ind) const {
    string corner = getCornerColorString(ind);

    uint8_t ret = 0;
    for (auto c: corner) {
        if (c != 'W' && c != 'Y') continue;
        if (c == 'Y') {
            ret |= (1 << 2);
        }
    }

    for (auto c: corner) {
        if (c != 'R' && c != 'O') continue;
        if (c == 'O') {
            ret |= (1 << 1);
        }
    }

    for (auto c: corner) {
        if (c != 'B' && c != 'G') continue;
        if (c == 'G') {
            ret |= (1 << 0);
        }
    }
    return ret;
}

uint8_t RubiksCube::getCornerOrientation(uint8_t ind) const {
    string corner = getCornerColorString(ind);

    string actual_str = "";

    for (auto c: corner) {
        if (c != 'W' && c != 'Y') continue;
        actual_str.push_back(c);
    }

    if (corner[1] == actual_str[0]) {
        return 1;
    } else if (corner[2] == actual_str[0]) {
        return 2;
    } else return 0;
}

