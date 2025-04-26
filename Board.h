#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "Bug.h"
#include "Position.h"
#include "SuperBug.h"
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
    int countAliveBugs() const;
    std::string getBugType(Bug* bug) const;
    const std::vector<std::unique_ptr<Bug>>& getBugs() const { return bugs; }
    std::string directionToString(Direction dir) const;

    void addSuperBug();
    void handleSuperBugFights();
    SuperBug* getSuperBug() const;


};