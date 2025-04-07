#include "Board.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>
   using namespace std;

void Board::initializeBoard(const std::string& filename) {
    if(initialized) {
        cout << "Board already initialized!\n";
        return;
    }

    ifstream file(filename);
    string line;

    while(getline(file, line)) {
        stringstream ss(line);
        vector<string> tokens;
        string token;

        while(getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if(tokens.size() >= 6) {
            int id = stoi(tokens[1]);
            int x = stoi(tokens[2]);
            int y = stoi(tokens[3]);
            Direction dir = static_cast<Direction>(stoi(tokens[4]));
            int size = stoi(tokens[5]);

            //if its a crawler "C"
            if(tokens[0] == "C") {
                bugs.emplace_back(make_unique<Crawler>(id, x, y, dir, size));
            }
            //if its a hopper "H"
            else if(tokens[0] == "H" && tokens.size() == 7) {
                int hopLength = stoi(tokens[6]);
                bugs.emplace_back(make_unique<Hopper>(id, x, y, dir, size, hopLength));
            }
            // if its a crissC=cross "X"
            else if(tokens[0] == "X" && tokens.size() == 7) {
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
    switch(dir) {
        case Direction::North: return "North";
        case Direction::East: return "East";
        case Direction::South: return "South";
        case Direction::West: return "West";
        default: return "Unknown";
    }
}
//
// void Board::displayAllBugs() const {
//     if(!initialized) {
//         cout << "Error: Board not initialized!\n";
//         return;
//     }
//     for(const auto& crawler : crawlers) {
//         Position pos = crawler->getPosition();
//       cout << crawler->getId() << " Crawler ("
//                   << pos.x << "," << pos.y << ") "
//                   << crawler->getSize() << " "
//                   << directionToString(crawler->getDirection()) << " "
//                   << (crawler->isAlive() ? "Alive" : "Dead") << "\n";
//     }
// }
//
// void Board::findBug(int id) const {
//     if(!initialized) {
//         cout << "Error: Board not initialized!\n";
//         return;
//     }
//     for(const auto& crawler : crawlers) {
//         if(crawler->getId() == id) {
//             Position pos = crawler->getPosition();
//            cout << "Bug found: " << crawler->getId() << " Crawler ("
//                       << pos.x << "," << pos.y << ") "
//                       << crawler->getSize() << " "
//                       << directionToString(crawler->getDirection()) << " "
//                       << (crawler->isAlive() ? "Alive" : "Dead") << "\n";
//             return;
//         }
//     }
//    cout << "Bug " << id << " not found.\n";
// }
//
// void Board::tapBoard() {
//     for(auto& crawler : crawlers) {
//         if(crawler->isAlive()) {
//             crawler->move();
//         }
//     }
//     handleFights();
// }
//
// void Board::handleFights() {
//    map<std::pair<int, int>, vector<Crawler*>> cellMap;
//
//     for(auto& crawler : crawlers) {
//         if(crawler->isAlive()) {
//             Position pos = crawler->getPosition();
//             cellMap[{pos.x, pos.y}].push_back(crawler.get());
//         }
//     }
//
//     for(auto& [pos, bugs] : cellMap) {
//         if(bugs.size() > 1) {
//             Crawler* winner = bugs[0];
//             for(auto bug : bugs) {
//                 if(bug->getSize() > winner->getSize()) {
//                     winner = bug;
//                 }
//             }
//
//             for(auto bug : bugs) {
//                 if(bug != winner) {
//                     bug->setAlive(false);
//                     bug->setKilledBy(winner->getId());
//                     winner->setSize(winner->getSize() + bug->getSize());
//                 }
//             }
//         }
//     }
// }
//
// void Board::displayLifeHistory() const {
//     for(const auto& crawler : crawlers) {
//        cout << crawler->getId() << " Crawler Path: ";
//         for(const auto& pos : crawler->getPath()) {
//             cout << "(" << pos.x << "," << pos.y << ")";
//             if(&pos != &crawler->getPath().back()) {
//                 cout << ",";
//             }
//         }
//         if(!crawler->isAlive()) {
//             cout << " Eaten by " << crawler->getKilledBy();
//         }
//       cout << "\n";
//     }
// }
//
// void Board::displayAllCells() const {
//     map<std::pair<int, int>, vector<int>> cellMap;
//
//     for(const auto& crawler : crawlers) {
//         if(crawler->isAlive()) {
//             Position pos = crawler->getPosition();
//             cellMap[{pos.x, pos.y}].push_back(crawler->getId());
//         }
//     }
//
//     for(int y = 0; y < 10; y++) {
//         for(int x = 0; x < 10; x++) {
//            cout << "(" << x << "," << y << "): ";
//             if(cellMap.count({x, y})) {
//                 for(size_t i = 0; i < cellMap[{x, y}].size(); i++) {
//                    cout << "Crawler " << cellMap[{x, y}][i];
//                     if(i != cellMap[{x, y}].size() - 1) {
//                        cout << ", ";
//                     }
//                 }
//             } else {
//                 cout << "empty";
//             }
//            cout << "\n";
//         }
//     }
// }
// // https://stackoverflow.com/questions/21521282/basic-timer-with-stdthread-and-stdchrono
// void Board::runSimulation(int taps) {
//     for(int i = 0; i < taps; i++) {
//         tapBoard();
//        this_thread::sleep_for(chrono::milliseconds(100));
//     }
// }
// void Board::writeLifeHistoryToFile(const string& filename) const {
//     ofstream outFile(filename);
//     if(!outFile) {
//        cerr << "Error opening file for writing!\n";
//         return;
//     }
//
//     for(const auto& crawler : crawlers) {
//         outFile << crawler->getId() << " Crawler Path: ";
//         for(const auto& pos : crawler->getPath()) {
//             outFile << "(" << pos.x << "," << pos.y << ")";
//             if(&pos != &crawler->getPath().back()) {
//                 outFile << ",";
//             }
//         }
//         if(!crawler->isAlive()) {
//             outFile << " Eaten by " << crawler->getKilledBy();
//         }
//         outFile << "\n";
//     }
//
//     outFile.close();
//     cout << "Life history written to " << filename << "\n";
// }