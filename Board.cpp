//
// Created by tsits on 01/04/2025.
//
#include "Board.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Board::initializeBoard(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<std::string> tokens;
        std::string token;

        while(std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if(tokens.size() == 6 && tokens[0] == "C") {
            crawlers.emplace_back(std::make_unique<Crawler>(
                std::stoi(tokens[1]),  // ID
                std::stoi(tokens[2]),  // X
                std::stoi(tokens[3]),  // Y
                static_cast<Direction>(std::stoi(tokens[4])),  // Direction
                std::stoi(tokens[5])   // Size
            ));
        }
    }
    file.close();
    cerr << "Read " << crawlers.size() << " crawlers" << endl;  // degubbibg
}

std::string Board::directionToString(Direction dir) const {
    switch(dir) {
        case Direction::North: return "North";
        case Direction::East: return "East";
        case Direction::South: return "South";
        case Direction::West: return "West";
        default: return "Unknown";
    }
}

void Board::displayAllBugs() const {
    for(const auto& crawler : crawlers) {
        Position pos = crawler->getPosition();
        std::cout << crawler->getId() << " Crawler ("
                  << pos.x << "," << pos.y << ") "
                  << crawler->getSize() << " "
                  << directionToString(crawler->getDirection()) << " "
                  << (crawler->isAlive() ? "Alive" : "Dead") << "\n";
    }
}

void Board::findBug(int id) const {
    for(const auto& crawler : crawlers) {
        if(crawler->getId() == id) {
            Position pos = crawler->getPosition();
            std::cout << "Bug found: " << crawler->getId() << " Crawler ("
                      << pos.x << "," << pos.y << ") "
                      << crawler->getSize() << " "
                      << directionToString(crawler->getDirection()) << " "
                      << (crawler->isAlive() ? "Alive" : "Dead") << "\n";
            return;
        }
    }
    std::cout << "Bug " << id << " not found.\n";
}