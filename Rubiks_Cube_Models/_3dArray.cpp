//
// Created by satya on 16-07-2025.
//

#include "rubiksCube.h"

// All those fans, which are virtual or not-implemented in abstract class, will be defined here

class RubiksCube3dArray : public RubiksCube {

public:
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

    // Define a 3D array to represent the state of the cube.
    color cube[6][3][3]{} ; // cube[Face][row on that face][col on that face]

    // Constructor
    RubiksCube3dArray() {
        // Initialize the cube to solved state;
        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    auto const c = static_cast<color>(F) ;
                    // auto const c = color(F) ; //This will also work
                    cube[F][row][col] = c ;
                }
            }
        }
    }

    color getColor(RubiksCube::face F, unsigned row, unsigned col) const override{
        return cube[F][row][col] ;
    }

    bool isSolved() const override {
        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    auto const c = static_cast<color>(F) ;
                    if (cube[F][row][col] != c) return false ;
                }
            }
        }
        return true ;
    }

    // Will make changes to state when cube face F is rotated once clockwise
    RubiksCube3dArray& rotateCW(face F) {
        color temp_face[3][3] ;
        // Store the face you want to rotate in the temp_face 2d arr
        for (int row=0 ; row<3 ; row++) {
            for (int col=0 ; col<3 ; col++) {
                temp_face[row][col] = cube[F][row][col] ;
            }
        }

        // 1st row becomes last column
        for (int i=0 ; i<3 ; i++) cube[F][i][2] = temp_face[0][i] ;
        // last col becomes last row (inverted)
        for (int i=0 ; i<3 ; i++) cube[F][2][2-i] = temp_face[i][2] ;
        // last row --> first column
        for (int i=0 ; i<3 ; i++) cube[F][2-i][0] = temp_face[2][2-i] ;
        // first col --> first row
        for (int i=0 ; i<3 ; i++) cube[F][0][i] = temp_face[2-i][0] ;

        return *this ;
    }

    // Will make changes to state when cube face F is rotated once Anti-CW
    RubiksCube3dArray& rotateACW(face F) {
        color temp_face[3][3] ;
        // Store the face you want to rotate in the temp_face 2d arr
        for (int row=0 ; row<3 ; row++) {
            for (int col=0 ; col<3 ; col++) {
                temp_face[row][col] = cube[F][row][col] ;
            }
        }

        // the last column becomes 1st row
        for (int i=0 ; i<3 ; i++) cube[F][0][i] = temp_face[i][2] ;
        // last row becomes last col
        for (int i=0 ; i<3 ; i++) cube[F][i][2] = temp_face[2][2-i] ;
        //  first column --> last row
        for (int i=0 ; i<3 ; i++) cube[F][2][2-i] = temp_face[2-i][0] ;
        // first row --> first col
        for (int i=0 ; i<3 ; i++) cube[F][2-i][0] = temp_face[0][i] ;

        return *this;
    }

    //IMPLEMENT 18 BASIC MOVES :-

    // Using 1 single move_helper Fxn :-
    RubiksCube3dArray& move_helper(face const F, vector<face> const adj_face, move_type MT) override{
        face const AF1 = adj_face[0], AF2 = adj_face[1], AF3 = adj_face[2], AF4 = adj_face[3] ;

        // Make a copy of cube's current state
        color temp_cube[6][3][3] ;
        for (int i = 0 ; i<6 ; i++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube[i][row][col] = cube[i][row][col] ;
                }
            }
        }

        if (MT == M1) {
            rotateCW(F) ; // First perform rotate action on the given Face itself
            // Then perform changes on other faces due to given move:
            // make changes in state of cube due to rotation of cube.
            // AF2(adjacent face 2), row=0 --will--become--> AF1(adjacent face 1) , row=0 ;
            for (int i=0 ; i<3 ; i++) cube[AF2][0][i] = temp_cube[AF1][0][i] ;
            // AF3, row=0 --will--become--> AF2 , row=0 ;
            for (int i=0 ; i<3 ; i++) cube[AF3][0][i] = temp_cube[AF2][0][i] ;
            // AF4, row=0 --will--become--> AF3 , row=0 ;
            for (int i=0 ; i<3 ; i++) cube[AF4][0][i] = temp_cube[AF3][0][i] ;
            // AF1, row=0 --will--become--> AF4 , row=0 ;
            for (int i=0 ; i<3 ; i++) cube[AF1][0][i] = temp_cube[AF4][0][i] ;
        }
        else if (MT==M2) {
            rotateCW(F) ; // First perform rotate action on the given Face itself
            rotateCW(F) ;
            // Then perform changes on other faces due to given move:
            // make changes in state of cube due to rotation of cube u() .
            // AF3, row=0 --will--become--> AF1 , row=0 ;
            for (int i=0 ; i<3 ; i++) cube[AF3][0][i] = temp_cube[AF1][0][i] ;
            // AF4, row=0 --will--become--> AF2 , row=0 ;
            for (int i=0 ; i<3 ; i++) cube[AF4][0][i] = temp_cube[AF2][0][i] ;
            // AF1, row=0 --will--become--> AF3 , row=0 ;
            for (int i=0 ; i<3 ; i++) cube[AF1][0][i] = temp_cube[AF3][0][i] ;
            // AF2, row=0 --will--become--> AF4 , row=0 ;
            for (int i=0 ; i<3 ; i++) cube[AF2][0][i] = temp_cube[AF4][0][i] ;
        }
        else if (MT==MPRIME) {
            rotateACW(F) ;
            // AF1(adjacent face 1), row=0 --will--become--> AF2(adjacent face 2) , row=0 ;
            for (int i=0 ; i<3 ; i++) cube[AF1][0][i] = temp_cube[AF2][0][i] ;
            // AF2, row=0 --will--become--> AF3 , row=0 ;
            for (int i=0 ; i<3 ; i++) cube[AF2][0][i] = temp_cube[AF3][0][i] ;
            // AF3, row=0 --will--become--> AF4 , row=0 ;
            for (int i=0 ; i<3 ; i++) cube[AF3][0][i] = temp_cube[AF4][0][i] ;
            // AF4, row=0 --will--become--> AF1 , row=0 ;
            for (int i=0 ; i<3 ; i++) cube[AF4][0][i] = temp_cube[AF1][0][i] ;
        }

        return *this ;
    }

    // Using 18 different individual fans
    //---------------------------UP FACE MOVES---------------------------
    RubiksCube3dArray& u() override{
        rotateCW(UP) ; // First perform rotate action on Face
        // Then perform changes on other face due to u() ;
        color temp_cube[6][3][3] ;

        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube[F][row][col] = cube[F][row][col] ;
                }
            }
        }

        // make changes in state of cube due to rotation of cube u() .
        // LEFT face, row=0 --will--become--> FRONT Face, row=0 ;
        for (int i=0 ; i<3 ; i++) cube[LEFT][0][i] = temp_cube[FRONT][0][i] ;
        // BACK face, row=0 --will--become--> LEFT Face, row=0 ;
        for (int i=0 ; i<3 ; i++) cube[BACK][0][i] = temp_cube[LEFT][0][i] ;
        // RIGHT face, row=0 --will--become--> BACK Face, row=0 ;
        for (int i=0 ; i<3 ; i++) cube[RIGHT][0][i] = temp_cube[BACK][0][i] ;
        // FRONT face, row=0 --will--become--> RIGHT Face, row=0 ;
        for (int i=0 ; i<3 ; i++) cube[FRONT][0][i] = temp_cube[RIGHT][0][i] ;

        return *this ;
    }

    RubiksCube3dArray& u2() override{
        u();
        u();
        return *this ;
    }

    RubiksCube3dArray& uPrime() override{
        rotateACW(UP) ; // First perform rotate action on Face
        // Then perform changes on other face due to u() ;
        color temp_cube[6][3][3] ;

        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube[F][row][col] = cube[F][row][col] ;
                }
            }
        }

        // make changes in state of cube due to rotation of cube u() .
        // FRONT face, row=0 --will--become--> LEFT Face, row=0 ;
        for (int i=0 ; i<3 ; i++) cube[FRONT][0][i] = temp_cube[LEFT][0][i] ;
        // LEFT face, row=0 --will--become--> BACK Face, row=0 ;
        for (int i=0 ; i<3 ; i++) cube[LEFT][0][i] = temp_cube[BACK][0][i] ;
        // BACK face, row=0 --will--become--> RIGHT Face, row=0 ;
        for (int i=0 ; i<3 ; i++) cube[BACK][0][i] = temp_cube[RIGHT][0][i] ;
        // RIGHT face, row=0 --will--become--> FRONT Face, row=0 ;
        for (int i=0 ; i<3 ; i++) cube[RIGHT][0][i] = temp_cube[FRONT][0][i] ;

        return *this ;
    }

    //---------------------------LEFT FACE MOVES---------------------------
    RubiksCube3dArray& l() override {
        return *this ;
    }
    RubiksCube3dArray& l2() override {
        return *this ;
    }
    RubiksCube3dArray& lPrime() override {
        return *this ;
    }
    //---------------------------FRONT FACE MOVES---------------------------
    RubiksCube3dArray& f() override {
        return *this ;
    }
    RubiksCube3dArray& f2() override {
        return *this ;
    }
    RubiksCube3dArray& fPrime() override {
        return *this ;
    }
    //---------------------------RIGHT FACE MOVES---------------------------
    RubiksCube3dArray& r() override {
        return *this ;
    }
    RubiksCube3dArray& r2() override {
        return *this ;
    }
    RubiksCube3dArray& rPrime() override {
        return *this ;
    }
    //---------------------------BACK FACE MOVES---------------------------
    RubiksCube3dArray& b() override {
        return *this ;
    }
    RubiksCube3dArray& b2() override {
        return *this ;
    }
    RubiksCube3dArray& bPrime() override {
        return *this ;
    }
    //---------------------------DOWN FACE MOVES---------------------------
    RubiksCube3dArray& d() override {
        return *this ;
    }
    RubiksCube3dArray& d2() override {
        return *this ;
    }
    RubiksCube3dArray& dPrime() override {
        return *this ;
    }
    //---------------------------x FACE MOVES Ends here x---------------------------

    // Now let's define some operators for our object: -
    bool operator==(const RubiksCube3dArray & rk) const {
        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    if (cube[F][row][col] != rk.cube[F][row][col]) return false ;
                }
            }
        }
        return true;
    }

    RubiksCube3dArray& operator=(const RubiksCube3dArray& rk) {
        if (this ==  &rk) return *this ;

        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    cube[F][row][col] = rk.cube[F][row][col] ;
                }
            }
        }
        return *this ;
    }

};

// Custom Hashing Fxn for this model
struct Hash3dArray {
    size_t operator()(const RubiksCube3dArray &r1) const {
        string str ;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    str += (RubiksCube3dArray::getColorLetter(r1.cube[i][j][k]));
                }
            }
        }
        return hash<string>()(str);
    }

};
