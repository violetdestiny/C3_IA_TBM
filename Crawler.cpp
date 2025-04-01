//
// Created by tsits on 01/04/2025.
//

#include "Crawler.h"
#include <cstdlib> // for the rand
using namespace std;

Crawler::Crawler(int id, int x, int y, Direction dir, int size)
    : id(id), position(x, y), direction(dir), size(size), alive(true), killedBy(-1) {
    path.push_back(position); // Add initial position to path
}

void Crawler::move() {
    if (!alive) return;

    // Change direction if blocked
    while(isWayBlocked()) {
        direction = static_cast<Direction>((rand() % 4) + 1);
    }

    // Update position based on direction
    switch(direction) {
        case Direction::North: position.y--; break;
        case Direction::East: position.x++; break;
        case Direction::South: position.y++; break;
        case Direction::West: position.x--; break;
    }

    path.push_back(position);
}

bool Crawler::isWayBlocked() const {
    switch(direction) {
        case Direction::North: return position.y == 0;
        case Direction::East: return position.x == 9;
        case Direction::South: return position.y == 9;
        case Direction::West: return position.x == 0;
        default: return false;
    }
}