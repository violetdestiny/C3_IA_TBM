//
// Created by tsits on 01/04/2025.
//

#include "Board.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void Board::initializeBoard(const std::string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        char type;
        int id, x, y, dir, size;

        ss >> type >> ws;
        ss >> id; ss.ignore();
        ss >> x; ss.ignore();
        ss >> y; ss.ignore();
        ss >> dir; ss.ignore();
        ss >> size;

        if(type == 'C') {
            crawlers.emplace_back( make_unique<Crawler>(
                    id, x, y, static_cast<Direction>(dir), size
                )
            );
        }
    }
    file.close();
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
void Board::displayAllBugs() const {
    for (const auto& crawler : crawlers) {
        Position pos = crawler->getPosition();
        cout << crawler->getId() <<
            " Crawler ("<< pos.x << "," << pos.y << ") "
                  << crawler->getSize() << " "
                  << directionToString(crawler->getDirection()) << " "
                  << (crawler->isAlive() ? "Alive" : "Dead") << "\n";
    }
}

void Board::findBug(int id) const {
    for (const auto& crawler : crawlers) {
        if (crawler->getId() == id) {
            Position pos = crawler->getPosition();
            cout << "Bug found: " << crawler->getId() << " Crawler ("
                      << pos.x << "," << pos.y << ") "
                      << crawler->getSize() << " "
                      << directionToString(crawler->getDirection()) << " "
                      << (crawler->isAlive() ? "Alive" : "Dead") << "\n";
            return;
        }
    }
    cout << "Bug " << id << " not found.\n";
}