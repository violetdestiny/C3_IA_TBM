//
// Created by tsits on 07/04/2025.
//

#include "Hopper.h"
#include <cstdlib>

void Hopper::move() {
    if (!alive) return;

    while(isWayBlocked()) {
        direction = static_cast<Direction>((rand() % 4) + 1); //change direction
    }

    switch(direction) {
        case Direction::North:
            position.y = (position.y - hopLength < 0) ? 0 : position.y - hopLength;
        break;
        case Direction::East:
            position.x = (position.x + hopLength > 9) ? 9 : position.x + hopLength;
        break;
        case Direction::South:
            position.y = (position.y + hopLength > 9) ? 9 : position.y + hopLength;
        break;
        case Direction::West:
            position.x = (position.x - hopLength < 0) ? 0 : position.x - hopLength;
        break;
        case Direction::NorthEast:
        case Direction::SouthEast:
        case Direction::SouthWest:
        case Direction::NorthWest:
            // Handle these cases or add a default case
            break;
    }

    path.push_back(position);
}
