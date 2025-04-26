//
// Created by tsits on 01/04/2025.
//

#ifndef CRAWLER_H
#define CRAWLER_H

#include "Bug.h"

class Crawler : public Bug {
public:
    Crawler(int id, int x, int y, Direction dir, int size)
        : Bug(id, x, y, dir, size) {}

    void move() override;
};

#endif //CRAWLER_H