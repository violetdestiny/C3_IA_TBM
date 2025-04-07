//
// Created by tsits on 07/04/2025.
//

#include "CrissCross.h"
#include <cstdlib>
#include <iostream>

CrissCross::CrissCross(int id, int x, int y, Direction dir1, Direction dir2, int size)
    : Bug(id, x, y, dir1, size), currentPhase(Phase::Primary),
      primaryDirection(dir1), secondaryDirection(dir2) {}

void CrissCross::move() {
    if (!alive) return;

    if (isDiagonalWayBlocked()) {
        reverseDirection();
    }

    // Move based on current phase
    switch (currentPhase == Phase::Primary ? primaryDirection : secondaryDirection) {
        case Direction::NorthEast:
            position.x++;
            position.y--;
            break;
        case Direction::SouthEast:
            position.x++;
            position.y++;
            break;
        case Direction::SouthWest:
            position.x--;
            position.y++;
            break;
        case Direction::NorthWest:
            position.x--;
            position.y--;
            break;
        default:
            // If somehow we get a non-diagonal direction
            currentPhase = Phase::Primary;
            primaryDirection = static_cast<Direction>((rand() % 4) + 5); // Random diagonal
            return;
    }

    // Ensure we stay within bounds
    position.x = std::max(0, std::min(9, position.x));
    position.y = std::max(0, std::min(9, position.y));

    path.push_back(position);

    // Switch phase for next move
    currentPhase = (currentPhase == Phase::Primary) ? Phase::Secondary : Phase::Primary;
}

bool CrissCross::isDiagonalWayBlocked() const {
    Direction currentDir = (currentPhase == Phase::Primary) ? primaryDirection : secondaryDirection;

    switch (currentDir) {
        case Direction::NorthEast:
            return position.x >= 9 || position.y <= 0;
        case Direction::SouthEast:
            return position.x >= 9 || position.y >= 9;
        case Direction::SouthWest:
            return position.x <= 0 || position.y >= 9;
        case Direction::NorthWest:
            return position.x <= 0 || position.y <= 0;
        default:
            return true;
    }
}

void CrissCross::reverseDirection() {
    if (currentPhase == Phase::Primary) {
        switch (primaryDirection) {
            case Direction::NorthEast: primaryDirection = Direction::SouthWest; break;
            case Direction::SouthEast: primaryDirection = Direction::NorthWest; break;
            case Direction::SouthWest: primaryDirection = Direction::NorthEast; break;
            case Direction::NorthWest: primaryDirection = Direction::SouthEast; break;
            default: break;
        }
    } else {
        switch (secondaryDirection) {
            case Direction::NorthEast: secondaryDirection = Direction::SouthWest; break;
            case Direction::SouthEast: secondaryDirection = Direction::NorthWest; break;
            case Direction::SouthWest: secondaryDirection = Direction::NorthEast; break;
            case Direction::NorthWest: secondaryDirection = Direction::SouthEast; break;
            default: break;
        }
    }
}

