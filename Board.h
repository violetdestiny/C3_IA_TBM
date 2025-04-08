#ifndef BOARD_H
#define BOARD_H

#include "Bug.h"
#include "Hopper.h"
#include "CrissCross.h"
#include "Crawler.h"
#include <vector>
#include <memory>
#include <string>
#include <utility>  // For std::pair
#include <map>
#include <algorithm>
#include <chrono>

struct BugResult {
    int id;
    std::string type;
    int size;
    int kills;
};

class Board {
    std::vector<std::unique_ptr<Bug>> bugs;
    bool initialized = false;

    std::string directionToString(Direction dir) const;
    void handleFights();
    std::string getBugType(Bug* bug) const;

public:
    void initializeBoard(const std::string& filename);
    void displayAllBugs() const;
    void findBug(int id) const;
    void tapBoard();
    void displayLifeHistory() const;
    void displayAllCells() const;
    void runSimulation(int taps);
    void writeLifeHistoryToFile(const std::string& filename) const;

    bool isInitialized() const { return initialized; }
    int countAliveBugs() const;
    std::pair<int, std::vector<BugResult>> runBattleRoyale(); //  https://youtu.be/XO3etcSj_Po?si=qSo32kRUBD35HZPi

    Board() = default;
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};

#endif