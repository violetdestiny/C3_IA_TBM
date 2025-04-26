#include "Board.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <map>
#include "Crawler.h"
#include "Hopper.h"
#include "CrissCross.h"

using namespace std;

void Board::initializeBoard(const std::string& filename) {
    if (initialized) {
        cout << "Board already initialized!\n";
        return;
    }

    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> tokens;
        string token;

        // Split line by commas
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 6) {
            int id = stoi(tokens[1]);
            int x = stoi(tokens[2]);
            int y = stoi(tokens[3]);
            Direction dir = static_cast<Direction>(stoi(tokens[4]));
            int size = stoi(tokens[5]);

            // Create appropriate bug type
            // if its a crawler "C"
            if (tokens[0] == "C") {
                bugs.emplace_back(make_unique<Crawler>(id, x, y, dir, size));
            }
            // if its a hopper "H"
            else if (tokens[0] == "H" && tokens.size() == 7) {
                int hopLength = stoi(tokens[6]);
                bugs.emplace_back(make_unique<Hopper>(id, x, y, dir, size, hopLength));
            }
            // if its a crisscross "X"
            else if (tokens[0] == "X" && tokens.size() == 7) {
                Direction dir1 = static_cast<Direction>(stoi(tokens[4]));
                Direction dir2 = static_cast<Direction>(stoi(tokens[6]));
                bugs.emplace_back(make_unique<CrissCross>(id, x, y, dir1, dir2, size));
            }
        }
    }
    file.close();
    initialized = true;
}

string Board::directionToString(Direction dir) const {
    switch (dir) {
        case Direction::North: return "North";
        case Direction::East: return "East";
        case Direction::South: return "South";
        case Direction::West: return "West";
        case Direction::NorthEast: return "NorthEast";
        case Direction::SouthEast: return "SouthEast";
        case Direction::SouthWest: return "SouthWest";
        case Direction::NorthWest: return "NorthWest";
        default: return "Unknown";
    }
}

void Board::displayAllBugs() const {
    if (!initialized) {
        cout << "Error: Board not initialized!\n";
        return;
    }
    for (const auto& bug : bugs) {
        Position pos = bug->getPosition();
        cout << bug->getId() << " ";

        // Show bug type
        if (dynamic_cast<Crawler*>(bug.get())) {
            cout << "Crawler ";
        } else if (dynamic_cast<Hopper*>(bug.get())) {
            cout << "Hopper ";
        } else if (dynamic_cast<CrissCross*>(bug.get())) {
            cout << "CrissCross ";
        }

        cout << "(" << pos.x << "," << pos.y << ") "
             << bug->getSize() << " "
             << directionToString(bug->getDirection()) << " "
             << (bug->isAlive() ? "Alive" : "Dead") << "\n";
    }
}

void Board::findBug(int id) const {
    if (!initialized) {
        cout << "Error: Board not initialized!\n";
        return;
    }

    for (const auto& bug : bugs) {
        if (bug->getId() == id) {
            Position pos = bug->getPosition();
            cout << "Bug found: " << bug->getId() << " ";
            cout << "(" << pos.x << "," << pos.y << ") "
                 << bug->getSize() << " "
                 << directionToString(bug->getDirection()) << " "
                 << (bug->isAlive() ? "Alive" : "Dead") << "\n";
            return;
        }
    }
    cout << "Bug " << id << " not found.\n";
}

void Board::tapBoard() {
    for (auto& bug : bugs) {
        if (bug->isAlive()) {
            bug->move();
        }
    }
    handleFights();
}

void Board::handleFights() {
    map<pair<int, int>, vector<Bug*>> cellMap;

    for (auto& bug : bugs) {
        if (bug->isAlive()) {
            Position pos = bug->getPosition();
            cellMap[{pos.x, pos.y}].push_back(bug.get());
        }
    }

    for (auto& [pos, bugsInCell] : cellMap) {
        if (bugsInCell.size() > 1) {
            Bug* winner = bugsInCell[0];

            // Find biggest bug
            for (auto bug : bugsInCell) {
                if (bug->getSize() > winner->getSize()) {
                    winner = bug;
                }
            }

            // Kill losers and grow winner
            for (auto bug : bugsInCell) {
                if (bug != winner) {
                    bug->setAlive(false);
                    bug->setKilledBy(winner->getId());
                    winner->setSize(winner->getSize() + bug->getSize());
                }
            }
        }
    }
}

void Board::displayLifeHistory() const {
    for (const auto& bug : bugs) {
        cout << bug->getId() << " ";

        if (dynamic_cast<Crawler*>(bug.get())) {
            cout << "Crawler ";
        } else if (dynamic_cast<Hopper*>(bug.get())) {
            cout << "Hopper ";
        } else if (dynamic_cast<CrissCross*>(bug.get())) {
            cout << "CrissCross ";
        }

        cout << "Path: ";

        for (const auto& pos : bug->getPath()) {
            cout << "(" << pos.x << "," << pos.y << ")";
            if (&pos != &bug->getPath().back()) {
                cout << ",";
            }
        }

        if (!bug->isAlive()) {
            cout << " Eaten by " << bug->getKilledBy();
        }
        cout << "\n";
    }
}

void Board::displayAllCells() const {
    map<pair<int, int>, vector<string>> cellMap;

    for (const auto& bug : bugs) {
        if (bug->isAlive()) {
            Position pos = bug->getPosition();
            string bugInfo = to_string(bug->getId());

            if (dynamic_cast<Crawler*>(bug.get())) {
                bugInfo += "C";
            } else if (dynamic_cast<Hopper*>(bug.get())) {
                bugInfo += "H";
            } else if (dynamic_cast<CrissCross*>(bug.get())) {
                bugInfo += "X";
            }

            cellMap[{pos.x, pos.y}].push_back(bugInfo);
        }
    }

    cout << "     ";
    for (int x = 0; x < 10; x++) {
        cout << "  " << x << "   ";
    }
    cout << "\n";

    cout << "    +";
    for (int x = 0; x < 10; x++) {
        cout << "-----+";
    }
    cout << "\n";

    for (int y = 0; y < 10; y++) {
        cout << " " << y << " |";
        for (int x = 0; x < 10; x++) {
            if (cellMap.count({x, y})) {
                if (cellMap[{x, y}].size() > 1) {
                    cout << " " << cellMap[{x, y}].size() << "x |";
                } else {
                    string bug = cellMap[{x, y}][0];
                    if (bug.length() == 2) cout << " ";
                    cout << bug << " |";
                }
            } else {
                cout << "     |";
            }
        }
        cout << "\n";
        cout << "    +";
        for (int x = 0; x < 10; x++) {
            cout << "-----+";
        }
        cout << "\n";
    }

    cout << "\nLegend:\n";
    cout << "  C = Crawler, H = Hopper, X = CrissCross\n";
    cout << "  #x = multiple bugs in cell (use Display All Bugs for details)\n";
}

void Board::runSimulation(int taps) {
    for (int i = 0; i < taps; i++) {
        tapBoard();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Board::writeLifeHistoryToFile(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing!\n";
        return;
    }

    for (const auto& bug : bugs) {
        outFile << bug->getId() << " ";

        if (dynamic_cast<Crawler*>(bug.get())) {
            outFile << "Crawler ";
        } else if (dynamic_cast<Hopper*>(bug.get())) {
            outFile << "Hopper ";
        } else if (dynamic_cast<CrissCross*>(bug.get())) {
            outFile << "CrissCross ";
        }

        outFile << "Path: ";
        for (const auto& pos : bug->getPath()) {
            outFile << "(" << pos.x << "," << pos.y << ")";
            if (&pos != &bug->getPath().back()) {
                outFile << ",";
            }
        }

        if (!bug->isAlive()) {
            outFile << " Eaten by " << bug->getKilledBy();
        }
        outFile << "\n";
    }

    outFile.close();
    cout << "Life history written to " << filename << "\n";
}

pair<int, vector<BugResult>> Board::runBattleRoyale() {
    int taps = 0;
    map<int, int> killCount;

    const auto startTime = chrono::steady_clock::now();
    bool timeLimitReached = false;

    for (const auto& bug : bugs) {
        killCount[bug->getId()] = 0;
    }

    while (countAliveBugs() > 1 && !timeLimitReached) {
        tapBoard();
        taps++;

        for (const auto& bug : bugs) {
            if (!bug->isAlive() && bug->getKilledBy() != -1) {
                killCount[bug->getKilledBy()]++;
            }
        }

        auto currentTime = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(currentTime - startTime);
        if (elapsed.count() >= 1) {
            timeLimitReached = true;
        }
    }

    vector<BugResult> results;
    vector<BugResult> allBugs;

    for (const auto& bug : bugs) {
        allBugs.push_back({
            bug->getId(),
            getBugType(bug.get()),
            bug->getSize(),
            killCount[bug->getId()]
        });
    }

    sort(allBugs.begin(), allBugs.end(), [](const BugResult& a, const BugResult& b) {
        if (a.kills == b.kills) return a.size > b.size;
        return a.kills > b.kills;
    });

    for (int i = 0; i < min(3, (int)allBugs.size()); i++) {
        results.push_back(allBugs[i]);
    }

    return {taps, results};
}

int Board::countAliveBugs() const {
    return count_if(bugs.begin(), bugs.end(), [](const unique_ptr<Bug>& bug) {
        return bug->isAlive();
    });
}

string Board::getBugType(Bug* bug) const {
    if (dynamic_cast<Crawler*>(bug)) return "Crawler";
    if (dynamic_cast<Hopper*>(bug)) return "Hopper";
    if (dynamic_cast<CrissCross*>(bug)) return "CrissCross";
    return "Unknown";
}


// for super bug


void Board::addSuperBug() {
    bugs.emplace_back(make_unique<SuperBug>(999, 0, 0, Direction::East, 30));
}

void Board::handleSuperBugFights() {
    if (!bugs.empty() && dynamic_cast<SuperBug*>(bugs.back().get())) {
        Position superPos = bugs.back()->getPosition();
        vector<Bug*> bugsInCell;

        for (auto& bug : bugs) {
            if (bug->isAlive() && bug.get() != bugs.back().get() &&
                bug->getPosition().x == superPos.x &&
                bug->getPosition().y == superPos.y) {
                bugsInCell.push_back(bug.get());
                }
        }

        for (auto bug : bugsInCell) {
            bug->setAlive(false);
            bug->setKilledBy(999);
            dynamic_cast<SuperBug*>(bugs.back().get())->addKill();
            bugs.back()->setSize(bugs.back()->getSize() + bug->getSize());
        }
    }
}

SuperBug* Board::getSuperBug() const {
    for (const auto& bug : bugs) {
        if (dynamic_cast<SuperBug*>(bug.get())) {
            return dynamic_cast<SuperBug*>(bug.get());
        }
    }
    return nullptr;
}