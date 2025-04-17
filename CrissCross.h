//
// Created by tsits on 07/04/2025.
//

#ifndef CRISSCROSS_H
#define CRISSCROSS_H
#include "Bug.h"



class CrissCross : public Bug {
private:
    enum class Phase { Primary, Secondary };
    Phase currentPhase;
    Direction primaryDirection;
    Direction secondaryDirection;

    void reverseDirection();
    bool isDiagonalWayBlocked() const;

public:
    CrissCross(int id, int x, int y, Direction dir1, Direction dir2, int size);
    void move() override;
};

#endif // CRISSCROSS_H
