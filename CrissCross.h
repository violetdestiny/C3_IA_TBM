//
// Created by tsits on 07/04/2025.
//

#ifndef CRISSCROSS_H
#define CRISSCROSS_H
#include "Bug.h"

//Moves in a zig zag formation

class CrissCross : public Bug {
private:
    enum class Phase { Primary, Secondary };
    Phase currentPhase;
    Direction primaryDirection; //alternates between 2 diagonal direction (could be like SouthWest that alternates with NorthEast)
    Direction secondaryDirection; // second direction to be alternated with (above could be NE while this one is SW and they alternate)

    void reverseDirection();
    bool isDiagonalWayBlocked() const;

public:
    CrissCross(int id, int x, int y, Direction dir1, Direction dir2, int size);
    void move() override;
};

#endif // CRISSCROSS_H
