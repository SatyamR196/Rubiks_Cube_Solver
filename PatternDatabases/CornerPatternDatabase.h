//
// Created by satya on 24-07-2025.
//

#ifndef CORNERPATTERNDATABASE_H
#define CORNERPATTERNDATABASE_H

#include "../Rubiks_Cube_Models/rubiksCube.h"
#include "PatternDatabase.h"
#include "PermutationIndexer.h"

class CornerPatternDatabase : public PatternDatabase {

    typedef RubiksCube::face F;

    PermutationIndexer<8> permIndexer;

public:
    CornerPatternDatabase();
    CornerPatternDatabase(uint8_t init_val);
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;

};

// class CornerPatternDatabase {
//     public:
//     // CornerPatternDatabase() {}
//
//     uint8_t getNumMoves(RubiksCube& cube) {
//         return 0 ; // doing this for now, will update later.
//     }
// };


#endif //CORNERPATTERNDATABASE_H
