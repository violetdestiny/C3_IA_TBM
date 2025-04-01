//
// Created by tsits on 01/04/2025.
//

#ifndef BOARD_H
#define BOARD_H
using namespace std;

#include "Crawler.h"
#include <vector>
#include <memory> // For smart pointers

class Board {
    vector<unique_ptr<Crawler>> crawlers; // Smart pointer container
    string directionToString(Direction dir) const;

public:

    void initializeBoard(const std::string& filename);
    void displayAllBugs() const;
    void findBug(int id) const;

    // Prevent copying
    Board() = default;
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};
#endif
