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
            auto const c = static_cast<color>(F) ;
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
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

    // Using 18 different individual fans
    //---------------------------UP FACE MOVES---------------------------
    RubiksCube3dArray& u() override{
        rotateCW(UP) ; // First perform rotate action on Face
        // Then perform changes on other face due to u() ;

        // Create a copy of cube of saving original state before move was performed
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
        u();
        u();
        u();
        return *this ;
    }

    //---------------------------LEFT FACE MOVES---------------------------
    RubiksCube3dArray& l() override {
        rotateCW(LEFT) ; // First perform rotate action on Face
        // Then perform changes on other face due to u() ;

        // Create a copy of cube of saving original state before move was performed
        color temp_cube[6][3][3] ;
        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube[F][row][col] = cube[F][row][col] ;
                }
            }
        }

        // make changes in state of cube due to rotation of cube u() .
        for (int i=0 ; i<3 ; i++) cube[UP][i][0] = temp_cube[BACK][2-i][2] ;
        for (int i = 0; i < 3; i++) cube[BACK][2 - i][2] = temp_cube[DOWN][i][0] ;
        for (int i = 0; i < 3; i++) cube[DOWN][i][0] = temp_cube[FRONT][i][0] ;
        for (int i = 0; i < 3; i++) cube[FRONT][i][0] = temp_cube[UP][i][0] ;

        return *this ;
    }
    RubiksCube3dArray& l2() override {
        l() ;
        l() ;
        return *this ;
    }
    RubiksCube3dArray& lPrime() override {
        l() ;
        l() ;
        l() ;
        return *this ;
    }
    //---------------------------FRONT FACE MOVES---------------------------
    RubiksCube3dArray& f() override {
        rotateCW(FRONT) ; // First perform rotate action on Face
        // Then perform changes on other face due to f() ;

        // Create a copy of cube of saving original state before move was performed
        color temp_cube[6][3][3] ;
        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube[F][row][col] = cube[F][row][col] ;
                }
            }
        }

        for (int i = 0; i < 3; i++) cube[RIGHT][i][0] = temp_cube[UP][2][i];
        for (int i = 0; i < 3; i++) cube[UP][2][i] = temp_cube[LEFT][2 - i][2];
        for (int i = 0; i < 3; i++) cube[LEFT][2 - i][2] = temp_cube[DOWN][0][2 - i];
        for (int i = 0; i < 3; i++) cube[DOWN][0][2 - i] = temp_cube[RIGHT][i][0];
        return *this ;
    }
    RubiksCube3dArray& f2() override {
        f();
        f();
        return *this ;
    }
    RubiksCube3dArray& fPrime() override {
        f();
        f();
        f();
        return *this ;
    }
    //---------------------------RIGHT FACE MOVES---------------------------
    RubiksCube3dArray& r() override {
        rotateCW(RIGHT) ;
        // Then perform changes on other face due to f() ;

        // Create a copy of cube of saving original state before move was performed
        color temp_cube[6][3][3] ;
        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube[F][row][col] = cube[F][row][col] ;
                }
            }
        }

        for (int i = 0; i < 3; i++) cube[BACK][i][0] = temp_cube[UP][2 - i][2];
        for (int i = 0; i < 3; i++) cube[UP][2 - i][2] = temp_cube[FRONT][2 - i][2];
        for (int i = 0; i < 3; i++) cube[FRONT][2 - i][2] = temp_cube[DOWN][2 - i][2];
        for (int i = 0; i < 3; i++) cube[DOWN][2 - i][2] = temp_cube[BACK][i][0];
        return *this ;
    }
    RubiksCube3dArray& r2() override {
        r();
        r();
        return *this ;
    }
    RubiksCube3dArray& rPrime() override {
        r();
        r();
        r();
        return *this ;
    }
    //---------------------------BACK FACE MOVES---------------------------
    RubiksCube3dArray& b() override {
        rotateCW(BACK) ;
        // Then perform changes on other face due to f() ;

        // Create a copy of cube of saving original state before move was performed
        color temp_cube[6][3][3] ;
        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube[F][row][col] = cube[F][row][col] ;
                }
            }
        }

        for (int i = 0; i < 3; i++) cube[LEFT][i][0] = temp_cube[UP][0][2 - i];
        for (int i = 0; i < 3; i++) cube[UP][0][2 - i] = temp_cube[RIGHT][2 - i][2];
        for (int i = 0; i < 3; i++) cube[RIGHT][2 - i][2] = temp_cube[DOWN][2][i];
        for (int i = 0; i < 3; i++) cube[DOWN][2][i] = temp_cube[LEFT][i][0];

        return *this ;
    }
    RubiksCube3dArray& b2() override {
        b();
        b() ;
        return *this ;
    }
    RubiksCube3dArray& bPrime() override {
        b();
        b();
        b();
        return *this ;
    }
    //---------------------------DOWN FACE MOVES---------------------------
    RubiksCube3dArray& d() override {
        rotateCW(DOWN) ;
        // Then perform changes on other face due to f() ;

        // Create a copy of cube of saving original state before move was performed
        color temp_cube[6][3][3] ;
        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube[F][row][col] = cube[F][row][col] ;
                }
            }
        }
        for (int i = 0; i < 3; i++) cube[RIGHT][2][i] = temp_cube[FRONT][2][i];
        for (int i = 0; i < 3; i++) cube[FRONT][2][i] = temp_cube[LEFT][2][i];
        for (int i = 0; i < 3; i++) cube[LEFT][2][i] = temp_cube[BACK][2][i];
        for (int i = 0; i < 3; i++) cube[BACK][2][i] = temp_cube[RIGHT][2][i];

        return *this ;
    }
    RubiksCube3dArray& d2() override {
        d();
        d();
        return *this ;
    }
    RubiksCube3dArray& dPrime() override {
        d();
        d();
        d();
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
    hash<string>h ;
    size_t operator()(const RubiksCube3dArray &r1) const {
        string str ;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    str += (RubiksCube3dArray::getColorLetter(r1.cube[i][j][k])) ;
                }
            }
        }
        // return hash<string>()(str);
        return h(str) ;
    }

};
