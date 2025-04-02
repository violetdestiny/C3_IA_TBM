//
// Created by tsits on 01/04/2025.
//

#ifndef CRAWLER_H
#define CRAWLER_H

#include "Position.h"
#include "Direction.h"
#include <list>
using namespace std;

//crawler using position and direction headers for navigation on the boards
class Crawler {
    int id;
    Position position; // coordinates for what cell bug is in
    Direction direction; // where bug is facing in case it's at the edge of the grid
    int size;
    bool alive;
    list<Position> path;  // logging the bugs travels
    int killedBy{};

public:
    Crawler(int id, int x, int y, Direction dir, int size);

    //board movement
    void move();
    bool isWayBlocked() const;

    //getters
    int getId() const { return id; }
    Position getPosition() const { return position; }
    Direction getDirection() const { return direction; }
    int getSize() const { return size; }
    bool isAlive() const { return alive; }
    const list<Position>& getPath() const { return path; }
    int getKilledBy() const { return killedBy; }

    //setters
    void setAlive(bool a) { alive = a; }
    void setDirection(Direction dir) { direction = dir; }
    void setSize(int s) { size = s; }
    void setKilledBy(int kb) { killedBy = kb; }
};


#endif //CRAWLER_H