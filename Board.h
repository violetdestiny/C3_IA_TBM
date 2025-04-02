#ifndef BOARD_H
#define BOARD_H

#include "Crawler.h"
#include <vector>
#include <memory> // for Smart pointers
#include <map>
#include <string>

class Board {
    std::vector<std::unique_ptr<Crawler>> crawlers;// Smart pointer container
    
    std::string directionToString(Direction dir) const;
    void handleFights();

public:
    void initializeBoard(const std::string& filename);
    void displayAllBugs() const;
    void findBug(int id) const;
    void tapBoard();
    void displayLifeHistory() const;
     void displayAllCells() const;
     void runSimulation(int taps);
    void writeLifeHistoryToFile(const std::string& filename) const;

    Board() = default;
    // Prevent copying
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};

#endif