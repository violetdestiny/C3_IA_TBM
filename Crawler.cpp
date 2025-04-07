#include "Crawler.h"
#include <cstdlib> // for the rand
using namespace std;

void Crawler::move() {
    if (!alive) return;

    // Change direction if blocked
    while(isWayBlocked()) {
        direction = static_cast<Direction>((rand() % 4) + 1);
    }

    // Update position based on direction
    Position pos = getPosition();
    switch(direction) {
        case Direction::North: position.y--; break;
        case Direction::East: position.x++; break;
        case Direction::South: position.y++; break;
        case Direction::West: position.x--; break;
    }

    // Ensure we stay within bounds (defensive programming)
    pos.x = max(0, min(9, pos.x));
    pos.y = max(0, min(9, pos.y));

    setPosition(pos); // Update position through base class}

}