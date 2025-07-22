//
// Created by satya on 19-07-2025.
//

#include "rubiksCube.h"

template<typename T>
class Array3D{
private :
    // depth = number of layers(grids), row = rows per layer, col = columns per row
    size_t depth, row, col ;
    vector<T>arr ;

public:

    Array3D(size_t depth, size_t row, size_t col){
        this->depth = depth ;
        this->row = row ;
        this->col = col ;
        arr.resize(depth*row*col) ;
    }
    // k <-> depth, i <-> row, j <-> col
    T& operator()(size_t k, size_t i, size_t j){
        size_t index = ( k*(row*col) + (i*col) + j) ;
        return arr[index] ;
    }
    // const version to allow creating const object of this class
    const T& operator()(size_t k, size_t i, size_t j) const {
        size_t index = ( k*(row*col) + (i*col) + j) ;
        return arr[index] ;
    }

};

class RubiksCube1dArray : public RubiksCube {
    private:

    public:

    // Create an instance of our 3D array which internally uses 1D array
    Array3D<color> cube ;
    // Constructor
    RubiksCube1dArray() : cube(6, 3, 3) {
        // Initialize the cube to solved state;
        for (int F = 0 ; F<6 ; F++) {
            auto const c = static_cast<color>(F) ;
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    // auto const c = color(F) ; //This will also work
                    cube(F,row,col) = c ;
                }
            }
        }
    }

    color getColor(RubiksCube::face F, unsigned row, unsigned col) const override{
        return cube(F,row,col) ;
    }

    bool isSolved() const override {
        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    auto const c = static_cast<color>(F) ;
                    if (cube(F,row,col) != c) return false ;
                }
            }
        }
        return true ;
    }


    // Will make changes to state when cube face F is rotated once clockwise
    RubiksCube1dArray& rotateCW(face F) {
        color temp_face[3][3] ;
        // Store the face you want to rotate in the temp_face 2d arr
        for (int row=0 ; row<3 ; row++) {
            for (int col=0 ; col<3 ; col++) {
                temp_face[row][col] = cube(F,row,col) ;
            }
        }

        // 1st row becomes last column
        for (int i=0 ; i<3 ; i++) cube(F,i,2) = temp_face[0][i] ;
        // last col becomes last row (inverted)
        for (int i=0 ; i<3 ; i++) cube(F,2,2-i) = temp_face[i][2] ;
        // last row --> first column
        for (int i=0 ; i<3 ; i++) cube(F,2-i,0) = temp_face[2][2-i] ;
        // first col --> first row
        for (int i=0 ; i<3 ; i++) cube(F,0,i) = temp_face[2-i][0] ;

        return *this ;
    }

    //IMPLEMENT 18 BASIC MOVES :-

    // Using 18 different individual fans
    //---------------------------UP FACE MOVES---------------------------
    RubiksCube1dArray& u() override{
        rotateCW(UP) ; // First perform rotate action on Face
        // Then perform changes on other face due to u() ;

        // Create a copy of cube of saving original state before move was performed
        Array3D<color>temp_cube(6,3,3) ;

        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube(F,row,col) = cube(F,row,col) ;
                }
            }
        }

        // make changes in state of cube due to rotation of cube u() .

        // LEFT face, row=0 --will--become--> FRONT Face, row=0 ;
        for (int i = 0; i < 3; i++) cube(LEFT, 0, i) = temp_cube(FRONT, 0, i);
        // BACK face, row=0 --will--become--> LEFT Face, row=0 ;
        for (int i = 0; i < 3; i++) cube(BACK, 0, i) = temp_cube(LEFT, 0, i);
        // RIGHT face, row=0 --will--become--> BACK Face, row=0 ;
        for (int i = 0; i < 3; i++) cube(RIGHT, 0, i) = temp_cube(BACK, 0, i);
        // FRONT face, row=0 --will--become--> RIGHT Face, row=0 ;
        for (int i = 0; i < 3; i++) cube(FRONT, 0, i) = temp_cube(RIGHT, 0, i);

        return *this ;
    }

    RubiksCube1dArray& u2() override{
        u();
        u();
        return *this ;
    }

    RubiksCube1dArray& uPrime() override{
        u();
        u();
        u();
        return *this ;
    }

    //---------------------------LEFT FACE MOVES---------------------------
    RubiksCube1dArray& l() override {
        rotateCW(LEFT) ; // First perform rotate action on Face
        // Then perform changes on other face due to l() ;

        // Create a copy of cube of saving original state before move was performed
        Array3D<color>temp_cube(6,3,3) ;

        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube(F,row,col) = cube(F,row,col) ;
                }
            }
        }

        // make changes in state of cube due to rotation of cube u()
        for (int i = 0; i < 3; i++) cube(UP, i, 0) = temp_cube(BACK, 2 - i, 2);
        for (int i = 0; i < 3; i++) cube(BACK, 2 - i, 2) = temp_cube(DOWN, i, 0);
        for (int i = 0; i < 3; i++) cube(DOWN, i, 0) = temp_cube(FRONT, i, 0);
        for (int i = 0; i < 3; i++) cube(FRONT, i, 0) = temp_cube(UP, i, 0);

        return *this ;
    }
    RubiksCube1dArray& l2() override {
        l() ;
        l() ;
        return *this ;
    }
    RubiksCube1dArray& lPrime() override {
        l() ;
        l() ;
        l() ;
        return *this ;
    }
    //---------------------------FRONT FACE MOVES---------------------------
    RubiksCube1dArray& f() override {
        rotateCW(FRONT) ; // First perform rotate action on Face
        // Then perform changes on other face due to f() ;

        // Create a copy of cube of saving original state before move was performed
        Array3D<color>temp_cube(6,3,3) ;

        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube(F,row,col) = cube(F,row,col) ;
                }
            }
        }

        for (int i = 0; i < 3; i++) cube(RIGHT, i, 0) = temp_cube(UP, 2, i);
        for (int i = 0; i < 3; i++) cube(UP, 2, i) = temp_cube(LEFT, 2 - i, 2);
        for (int i = 0; i < 3; i++) cube(LEFT, 2 - i, 2) = temp_cube(DOWN, 0, 2 - i);
        for (int i = 0; i < 3; i++) cube(DOWN, 0, 2 - i) = temp_cube(RIGHT, i, 0);

        return *this ;
    }
    RubiksCube1dArray& f2() override {
        f();
        f();
        return *this ;
    }
    RubiksCube1dArray& fPrime() override {
        f();
        f();
        f();
        return *this ;
    }
    //---------------------------RIGHT FACE MOVES---------------------------
    RubiksCube1dArray& r() override {
        rotateCW(RIGHT) ;
        // Then perform changes on other face due to r() ;

        // Create a copy of cube of saving original state before move was performed
        Array3D<color>temp_cube(6,3,3) ;

        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube(F,row,col) = cube(F,row,col) ;
                }
            }
        }

        for (int i = 0; i < 3; i++) cube(BACK, i, 0) = temp_cube(UP, 2 - i, 2);
        for (int i = 0; i < 3; i++) cube(UP, 2 - i, 2) = temp_cube(FRONT, 2 - i, 2);
        for (int i = 0; i < 3; i++) cube(FRONT, 2 - i, 2) = temp_cube(DOWN, 2 - i, 2);
        for (int i = 0; i < 3; i++) cube(DOWN, 2 - i, 2) = temp_cube(BACK, i, 0);

        return *this ;
    }
    RubiksCube1dArray& r2() override {
        r();
        r();
        return *this ;
    }
    RubiksCube1dArray& rPrime() override {
        r();
        r();
        r();
        return *this ;
    }
    //---------------------------BACK FACE MOVES---------------------------
    RubiksCube1dArray& b() override {
        rotateCW(BACK) ;
        // Then perform changes on other face due to b() ;

        // Create a copy of cube of saving original state before move was performed
        Array3D<color>temp_cube(6,3,3) ;

        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube(F,row,col) = cube(F,row,col) ;
                }
            }
        }

        for (int i = 0; i < 3; i++) cube(LEFT, i, 0) = temp_cube(UP, 0, 2 - i);
        for (int i = 0; i < 3; i++) cube(UP, 0, 2 - i) = temp_cube(RIGHT, 2 - i, 2);
        for (int i = 0; i < 3; i++) cube(RIGHT, 2 - i, 2) = temp_cube(DOWN, 2, i);
        for (int i = 0; i < 3; i++) cube(DOWN, 2, i) = temp_cube(LEFT, i, 0);


        return *this ;
    }
    RubiksCube1dArray& b2() override {
        b();
        b() ;
        return *this ;
    }
    RubiksCube1dArray& bPrime() override {
        b();
        b();
        b();
        return *this ;
    }
    //---------------------------DOWN FACE MOVES---------------------------
    RubiksCube1dArray& d() override {
        rotateCW(DOWN) ;
        // Then perform changes on other face due to d() ;

        // Create a copy of cube of saving original state before move was performed
        Array3D<color>temp_cube(6,3,3) ;

        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    temp_cube(F,row,col) = cube(F,row,col) ;
                }
            }
        }

        for (int i = 0; i < 3; i++) cube(RIGHT, 2, i) = temp_cube(FRONT, 2, i);
        for (int i = 0; i < 3; i++) cube(FRONT, 2, i) = temp_cube(LEFT, 2, i);
        for (int i = 0; i < 3; i++) cube(LEFT, 2, i) = temp_cube(BACK, 2, i);
        for (int i = 0; i < 3; i++) cube(BACK, 2, i) = temp_cube(RIGHT, 2, i);


        return *this ;
    }
    RubiksCube1dArray& d2() override {
        d();
        d();
        return *this ;
    }
    RubiksCube1dArray& dPrime() override {
        d();
        d();
        d();
        return *this ;
    }
    //---------------------------x FACE MOVES Ends here x---------------------------

    // Now let's define some operators for our object: -
    bool operator==(const RubiksCube1dArray & rk) const {
        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    if ( cube(F,row,col) != rk.cube(F,row,col) ) return false ;
                }
            }
        }
        return true;
    }

    RubiksCube1dArray& operator=(const RubiksCube1dArray& rk) {
        if (this ==  &rk) return *this ;

        for (int F = 0 ; F<6 ; F++) {
            for (int row=0 ; row<3 ; row++) {
                for (int col=0 ; col<3 ; col++) {
                    cube(F,row,col) = rk.cube(F,row,col) ;
                }
            }
        }
        return *this ;
    }

};

// Custom Hashing Fxn for this model
struct Hash1dArray {
    hash<string>h ;
    size_t operator()(const RubiksCube1dArray &r1) const {
        string str ;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    str += (RubiksCube1dArray::getColorLetter(r1.cube(i,j,k))) ;
                }
            }
        }
        // return hash<string>()(str);
        return h(str) ;
    }

};