//
// Created by tsits on 07/04/2025.
//

#ifndef BUG_H
#define BUG_H

#include "Position.h"
#include "Direction.h"
#include <list>
#include <array>
#include <stdlib.h>

class Bug {
protected:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    int killedBy;
    std::list<Position> path;

public:
    Bug(int id, int x, int y, Direction dir, int size)
        : id(id), position{x, y}, direction(dir), size(size),
          alive(true), killedBy(-1) {
        path.push_back(position);
    }

    virtual ~Bug() = default;


    virtual void move() = 0;

    bool isWayBlocked() const {
        switch(direction) {
            case Direction::North: return position.y == 0;
            case Direction::East: return position.x == 9;
            case Direction::South: return position.y == 9;
            case Direction::West: return position.x == 0;
            default: return false;
        }
    }

    void setPosition(const Position& pos) {
        position = pos;
        path.push_back(position);
    }

    Direction getRandomDirection() {
        static const std::array<Direction, 4> directions = {
            Direction::North, Direction::East, Direction::South, Direction::West
        };
        return directions[rand() % directions.size()];
    }

    int getId() const { return id; }
    Position getPosition() const { return position; }
    Direction getDirection() const { return direction; }
    int getSize() const { return size; }
    bool isAlive() const { return alive; }
    int getKilledBy() const { return killedBy; }
    const std::list<Position>& getPath() const { return path; }

    void setAlive(bool status) { alive = status; }
    void setKilledBy(int killer) { killedBy = killer; }
    void setSize(int newSize) { size = newSize; }
    void setDirection(Direction dir) { direction = dir; }
};

#endif // BUG_H