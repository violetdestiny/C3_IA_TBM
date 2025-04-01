//
// Created by tsits on 01/04/2025.
//

#ifndef POSITION_H
#define POSITION_H

struct Position {

    //coordinates
    int x;  // up
    int y;  // sideways

    // for sorting
    bool operator<(const Position& other) const {
        if(x == other.x) return y < other.y;
        return x < other.x;
    }
};
#endif //POSITION_H
