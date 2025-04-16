#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include "CrissCross.h"

struct BugResult {
    int id;
    std::string type;
    int size;
    int kills;
};

class Board {
private:
    std::vector<std::unique_ptr<Bug>> bugs;
    bool initialized = false;

    void handleFights();
    int countAliveBugs() const;
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
    std::pair<int, std::vector<BugResult>> runBattleRoyale();
    bool isInitialized() const { return initialized; }

    // SFML Visualization methods
    void draw(sf::RenderWindow& window) const;
    void drawGrid(sf::RenderWindow& window) const;
    void drawBugs(sf::RenderWindow& window) const;
};

#endif // BOARD_H