//
// Created by tsits on 01/04/2025.
//

#include "Crawler.h"
using namespace std;

Crawler::Crawler(int id, int x, int y, Direction dir, int size)
    : id(id), position(x, y), direction(dir), size(size), alive(true) {}
