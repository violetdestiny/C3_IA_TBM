//
// Created by tsits on 07/04/2025.
//

#ifndef HOPPER_H
#define HOPPER_H

#include "Bug.h"

class Hopper : public Bug {
private:
    int hopLength;

public:
    Hopper(int id, int x, int y, Direction dir, int size, int hopLength)
        : Bug(id, x, y, dir, size), hopLength(hopLength) {}

    void move() override;
    int getHopLength() const { return hopLength; }
};

#endif // HOPPER_H
