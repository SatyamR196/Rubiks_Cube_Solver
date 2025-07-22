//
// Created by satya on 20-07-2025.
//

#include "rubiksCube.h"

class RubiksCubebitBoard : public RubiksCube {
private:
public:
    // 6 faces, each face have 9 squares containing a color each, we need at least 3 bits
    // to represent a cell(square on face) as there are 6 unique colors possible(6 < 2^3)
    // Face layout and indexing :
    //         U             0
    //       L F R B  ---> 1 2 3 4
    //         D             5

    //            [U Face - 0]
    //              0  1  2
    //              3  4  5
    //              6  7  8
    //
    // [L Face -1] [F Face -2] [R Face -3] [B Face -4]
    // 0  1  2      0  1  2      0  1  2      0  1  2
    // 3  4  5      3  4  5      3  4  5      3  4  5
    // 6  7  8      6  7  8      6  7  8      6  7  8
    //
    //            [D Face - 5]
    //              0  1  2
    //              3  4  5
    //              6  7  8

    array<bitset<27>, 6> cube ;
    // Remember in bitset indexing start from right most bit as 0.

    RubiksCubebitBoard() {
        for (int F = 0 ; F<6 ; F++) {
            auto const c = static_cast<color>(F) ;
            for (int i = 0 ; i < 9 ; i++) {
                setColor(face(F),i,c) ;
            }
        }
    }

    // copy constructor
    RubiksCubebitBoard(const RubiksCubebitBoard& other) {
        for (int F = 0; F < 6; F++) {
            cube[F] = other.cube[F];
        }
    }

    void setColor(face F, unsigned cell_id, color c) {
        unsigned bitStart = cell_id*3 ;
        for (int i=0 ; i<3 ; i++) {
            // Easy implementation :
            cube[F][bitStart+i] =  (c >> i) & 1;

            // Also valid implementation :
            // if (c & (1<<i)) cube[F][bitStart+i] = true;
            // else cube[F][bitStart+i] = false;

            // also a valid implementation :
            // cube[F][bitStart+i] = ((1<<(2-i)) & c)!=0 ;
        }
    }

    color getColor(face F, unsigned cell_id) const{
        unsigned bitStart = cell_id*3 ;
        int c{} ;
        for (int i=0 ; i<3 ; i++) {
            c |= (cube[F][bitStart+i]<<i) ;
        }
        return color(c) ;
    }

    color getColor(face F, unsigned row, unsigned col) const override{
        unsigned cell_id = row*3 + col ;
        unsigned bitStart = cell_id*3 ;
        int c{} ;
        for (int i=0 ; i<3 ; i++) {
            c |= (cube[F][bitStart+i]<<i) ;
        }
        return color(c) ;
    }

    bool isSolved() const override {
        for (int F = 0 ; F<6 ; F++) {
            auto const c = static_cast<color>(F);
            for (int i = 0 ; i < 9 ; i++) {
                if (getColor(face(F), i) != c)
                    return false;
            }
        }
        return true;
    }

    // bool isSolved() const override {
    //     for (int F = 0 ; F<6 ; F++) {
    //         auto const c = static_cast<color>(F) ;
    //         for (int i = 0 ; i < 9 ; i++) {
    //             if (cube[F][i] != c) return false ;
    //         }
    //     }
    //     return true ;
    // }
    // Will make changes to state when cube face F is rotated once clockwise
    void rotateCW(face F) {
        const array<int, 8> from = {0, 1, 2, 5, 8, 7, 6, 3};
        const array<int, 8> to   = {2, 5, 8, 7, 6, 3, 0, 1};

        array<color, 8> temp;
        for (int i = 0; i < 8; i++) {
            // std::cerr << "Reading from " << from[i] << std::endl;
            temp[i] = getColor(F, from[i]);
        }
        for (int i = 0; i < 8; i++) {
            // std::cerr << "Reading from " << temp[i] << std::endl;
            setColor(F,to[i] ,temp[i]) ;
        }
        // cout<<"RETURN"<<endl;
        // *this ;
    }

    void cycleEdges(face F1, array<int, 3> F1_pos,
                    face F2, array<int, 3> F2_pos,
                    face F3, array<int, 3> F3_pos,
                    face F4, array<int, 3> F4_pos) {

        array<color, 3> F1_color{}, F2_color{}, F3_color{}, F4_color{};
        for (int i = 0; i < 3; ++i) {
            F1_color[i] = getColor(F1, F1_pos[i]);
            F2_color[i] = getColor(F2, F2_pos[i]);
            F3_color[i] = getColor(F3, F3_pos[i]);
            F4_color[i] = getColor(F4, F4_pos[i]);
        }
        for (int i = 0; i < 3; ++i) {
            setColor(F2, F2_pos[i], F1_color[i]);
            setColor(F3, F3_pos[i], F2_color[i]);
            setColor(F4, F4_pos[i], F3_color[i]);
            setColor(F1, F1_pos[i], F4_color[i]);
        }
    }

    // Using 18 different individual fans
    //---------------------------UP FACE MOVES---------------------------
    RubiksCubebitBoard& u() override{
        rotateCW(UP) ; // First perform rotate action on Face
        // cycleEdges(LEFT, {0,1,2}, FRONT, {0,1,2},
        //     RIGHT, {0,1,2},
        //     BACK, {0,1,2});
        //above one seems wrong :
        cycleEdges(LEFT, {0,1,2}, BACK, {0,1,2},
            RIGHT, {0,1,2},FRONT, {0,1,2});

        return *this ;
    }

    RubiksCubebitBoard& u2() override{
        u();
        u();
        return *this ;
    }

    RubiksCubebitBoard& uPrime() override{
        u();
        u();
        u();
        return *this ;
    }

    //---------------------------LEFT FACE MOVES---------------------------
    RubiksCubebitBoard& l() override{
        rotateCW(LEFT) ; // First perform rotate action on Face
        cycleEdges(UP, {0,3,6}, FRONT, {0,3,6},
            DOWN, {0,3,6},BACK, {8,5,2});

        return *this ;
    }

    RubiksCubebitBoard& l2() override{
        l();
        l();
        return *this ;
    }

    RubiksCubebitBoard& lPrime() override{
        l();
        l();
        l();
        return *this ;
    }

    //---------------------------FRONT FACE MOVES---------------------------
    RubiksCubebitBoard& f() override{
        rotateCW(FRONT) ; // First perform rotate action on Face
        cycleEdges(UP, {6,7,8}, RIGHT, {0,3,6},
            DOWN, {2,1,0}, LEFT, {8,5,2});

        return *this ;
    }

    RubiksCubebitBoard& f2() override{
        f();
        f();
        return *this ;
    }

    RubiksCubebitBoard& fPrime() override{
        f();
        f();
        f();
        return *this ;
    }

    //---------------------------RIGHT FACE MOVES---------------------------
    RubiksCubebitBoard& r() override{
        rotateCW(RIGHT) ; // First perform rotate action on Face
        cycleEdges(UP, {8,5,2}, BACK, {0,3,6},
            DOWN, {8,5,2}, FRONT, {8,5,2});

        return *this ;
    }

    RubiksCubebitBoard& r2() override{
        r();
        r();
        return *this ;
    }

    RubiksCubebitBoard& rPrime() override{
        r();
        r();
        r();
        return *this ;
    }

    //---------------------------BACK FACE MOVES---------------------------
    RubiksCubebitBoard& b() override{
        rotateCW(BACK) ; // First perform rotate action on Face
        cycleEdges(UP, {2,1,0}, LEFT, {0,3,6},
            DOWN, {6,7,8}, RIGHT, {8,5,2});

        return *this ;
    }

    RubiksCubebitBoard& b2() override{
        b();
        b();
        return *this ;
    }

    RubiksCubebitBoard& bPrime() override{
        b();
        b();
        b();
        return *this ;
    }

    //---------------------------DOWN FACE MOVES---------------------------
    RubiksCubebitBoard& d() override{
        rotateCW(DOWN) ; // First perform rotate action on Face
        // cycleEdges(LEFT, {6,7,8}, BACK, {6,7,8},
        //     RIGHT, {6,7,8}, FRONT, {6,7,8});
        cycleEdges(LEFT, {6,7,8}, FRONT, {6,7,8},
            RIGHT, {6,7,8}, BACK, {6,7,8});

        return *this ;
    }

    RubiksCubebitBoard& d2() override{
        d();
        d();
        return *this ;
    }

    RubiksCubebitBoard& dPrime() override{
        d();
        d();
        d();
        return *this ;
    }

    //---------------------------x FACE MOVES Ends here x---------------------------

    // Now let's define some operators for our object: -
    bool operator==(const RubiksCubebitBoard & rk) const {
        for (int F = 0 ; F<6 ; F++) {
            if (cube[F] != rk.cube[F]) return false ;
        }
        return true;
    }

    RubiksCubebitBoard& operator=(const RubiksCubebitBoard& rk) {
        if (this ==  &rk) return *this ;

        for (int F = 0 ; F<6 ; F++) {
            cube[F] = rk.cube[F] ;
        }
        return *this ;
    }
};

// Custom Hashing Fxn for this model
struct HashbitBoard {
    hash<string>h ;
    size_t operator()(const RubiksCubebitBoard &r1) const {
        string str ;
        for (int F = 0; F < 6; F++) {
            for (int i = 0; i < 27; i++) {
                str += (RubiksCubebitBoard::getColorLetter(r1.getColor(RubiksCubebitBoard::face(F),i))) ;
            }
        }
        // return hash<string>()(str);
        return h(str) ;
    }

};