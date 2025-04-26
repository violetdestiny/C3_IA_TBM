#include "Crawler.h"
#include <cstdlib> // for the rand
#include <iostream>
using namespace std;

//crawler wasnt moving
// void Crawler::move() {
//     if (!alive) {
//         //debugging
//         // cout << "Crawler " << id << " is dead\n";
//
//         Position newPos = position; // current position
//
//         return;
//     }
//
//     //debugging
//     // cout << "Crawler " << id << " at (" << position.x << "," << position.y
//     //     << ") facing " << static_cast<int>(direction) << " moving to ";
//
//     // Change direction if blocked
//     while(isWayBlocked()) {
//         direction = static_cast<Direction>((rand() % 4) + 1);
//     }
//
//     // Update position based on direction
//     Position pos = getPosition();
//     switch(direction) {
//         case Direction::North: position.y--; break;
//         case Direction::East: position.x++; break;
//         case Direction::South: position.y++; break;
//         case Direction::West: position.x--; break;
//         default:break;
//     }
//
//     pos.x = max(0, min(9, pos.x));
//     pos.y = max(0, min(9, pos.y));
//
//     setPosition(pos); // Update position through base class
//
//     //debugging
//     // cout << "(" << position.x << "," << position.y << ")\n";
//
// }
void Crawler::move() {
    if (!alive) return;

    Position newPos = position; // Start with current position

    // Try up to 4 times to find a valid direction
    for (int attempts = 0; attempts < 4; attempts++) {

        // If current direction is blocked, pick a new random one
        if (isWayBlocked()) {
            direction = static_cast<Direction>((rand() % 4) + 1);
            continue;
        }

        // Calculate new position
        switch(direction) {
            case Direction::North: newPos.y--; break;
            case Direction::East:  newPos.x++; break;
            case Direction::South: newPos.y++; break;
            case Direction::West:  newPos.x--; break;
        }
        break;
    }

    // Update position (even if it didn't change)
    setPosition(newPos);

    // Debuging
    // cout << "Crawler " << id << " at (" << position.x << "," << position.y
    //      << ") facing " << static_cast<int>(direction)
    //      << " moving to (" << newPos.x << "," << newPos.y << ")\n";
}