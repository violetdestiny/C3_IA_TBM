
#include "Board.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
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

            if(tokens[0] == "C") {
                bugs.emplace_back(make_unique<Crawler>(id, x, y, dir, size));
            }
            else if(tokens[0] == "H" && tokens.size() == 7) {
                int hopLength = stoi(tokens[6]);
                bugs.emplace_back(make_unique<Hopper>(id, x, y, dir, size, hopLength));
            }
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

static string directionToString(Direction dir) {
    switch(dir) {
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
    if(!initialized) {
        cout << "Error: Board not initialized!\n";
        return;
    }
    for(const auto& bug : bugs) {
        Position pos = bug->getPosition();
        cout << bug->getId() << " ";

        if(dynamic_cast<Crawler*>(bug.get())) {
            cout << "Crawler ";
        }
        else if(dynamic_cast<Hopper*>(bug.get())) {
            cout << "Hopper ";
        }
        else if(dynamic_cast<CrissCross*>(bug.get())) {
            cout << "CrissCross ";
        }

        cout << "(" << pos.x << "," << pos.y << ") "
             << bug->getSize() << " "
             << directionToString(bug->getDirection()) << " "
             << (bug->isAlive() ? "Alive" : "Dead") << "\n";
    }
}

void Board::findBug(int id) const {
    if(!initialized) {
        cout << "Error: Board not initialized!\n";
        return;
    }

    for(const auto& bug : bugs) {
        if(bug->getId() == id) {
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
    for(auto& bug : bugs) {
        if(bug->isAlive()) {
            bug->move();
        }
    }
    handleFights();
}

void Board::handleFights() {
    map<pair<int, int>, vector<Bug*>> cellMap;

    for(auto& bug : bugs) {
        if(bug->isAlive()) {
            Position pos = bug->getPosition();
            cellMap[{pos.x, pos.y}].push_back(bug.get());
        }
    }

    for(auto& [pos, bugsInCell] : cellMap) {
        if(bugsInCell.size() > 1) {
            Bug* winner = bugsInCell[0];
            for(auto bug : bugsInCell) {
                if(bug->getSize() > winner->getSize()) {
                    winner = bug;
                }
            }
            for(auto bug : bugsInCell) {
                if(bug != winner) {
                    bug->setAlive(false);
                    bug->setKilledBy(winner->getId());
                    winner->setSize(winner->getSize() + bug->getSize());
                }
            }
        }
    }
}

void Board::displayLifeHistory() const {
    for(const auto& bug : bugs) {
        cout << bug->getId() << " ";

        if(dynamic_cast<Crawler*>(bug.get())) {
            cout << "Crawler ";
        }
        else if(dynamic_cast<Hopper*>(bug.get())) {
            cout << "Hopper ";
        }
        else if(dynamic_cast<CrissCross*>(bug.get())) {
            cout << "CrissCross ";
        }

        cout << "Path: ";
        for(const auto& pos : bug->getPath()) {
            cout << "(" << pos.x << "," << pos.y << ")";
            if(&pos != &bug->getPath().back()) {
                cout << ",";
            }
        }

        if(!bug->isAlive()) {
            cout << " Eaten by " << bug->getKilledBy();
        }
        cout << "\n";
    }
}

void Board::displayAllCells() const {
    map<pair<int, int>, vector<string>> cellMap;

    for(const auto& bug : bugs) {
        if(bug->isAlive()) {
            Position pos = bug->getPosition();
            string bugInfo = to_string(bug->getId());
            if(dynamic_cast<Crawler*>(bug.get())) {
                bugInfo += "C";
            }
            else if(dynamic_cast<Hopper*>(bug.get())) {
                bugInfo += "H";
            }
            else if(dynamic_cast<CrissCross*>(bug.get())) {
                bugInfo += "X";
            }
            cellMap[{pos.x, pos.y}].push_back(bugInfo);
        }
    }

    cout << "     ";
    for(int x = 0; x < 10; x++) {
        cout << "  " << x << "   ";
    }
    cout << "\n";

    cout << "    +";
    for(int x = 0; x < 10; x++) {
        cout << "-----+";
    }
    cout << "\n";

    for(int y = 0; y < 10; y++) {
        cout << " " << y << " |";
        for(int x = 0; x < 10; x++) {
            if(cellMap.count({x, y})) {
                if(cellMap[{x, y}].size() > 1) {
                    cout << " " << cellMap[{x, y}].size() << "x |";
                }
                else {
                    string bug = cellMap[{x, y}][0];
                    if(bug.length() == 2) cout << " ";
                    cout << bug << " |";
                }
            }
            else {
                cout << "     |";
            }
        }
        cout << "\n";

        cout << "    +";
        for(int x = 0; x < 10; x++) {
            cout << "-----+";
        }
        cout << "\n";
    }

    cout << "\nLegend:\n";
    cout << "  C = Crawler, H = Hopper, X = CrissCross\n";
    cout << "  #x = multiple bugs in cell\n";
}

void Board::runSimulation(int taps) {
    for(int i = 0; i < taps; i++) {
        tapBoard();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Board::writeLifeHistoryToFile(const string& filename) const {
    ofstream outFile(filename);
    if(!outFile) {
        cerr << "Error opening file for writing!\n";
        return;
    }

    for(const auto& bug : bugs) {
        outFile << bug->getId() << " ";

        if(dynamic_cast<Crawler*>(bug.get())) {
            outFile << "Crawler ";
        }
        else if(dynamic_cast<Hopper*>(bug.get())) {
            outFile << "Hopper ";
        }
        else if(dynamic_cast<CrissCross*>(bug.get())) {
            outFile << "CrissCross ";
        }

        outFile << "Path: ";
        for(const auto& pos : bug->getPath()) {
            outFile << "(" << pos.x << "," << pos.y << ")";
            if(&pos != &bug->getPath().back()) {
                outFile << ",";
            }
        }

        if(!bug->isAlive()) {
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
    if(dynamic_cast<Crawler*>(bug)) return "Crawler";
    if(dynamic_cast<Hopper*>(bug)) return "Hopper";
    if(dynamic_cast<CrissCross*>(bug)) return "CrissCross";
    return "Unknown";
}

void Board::draw(sf::RenderWindow& window) const {
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        if (!font.loadFromFile("arial.ttf")) {
            return;
        }
        fontLoaded = true;
    }

    drawGrid(window, font);
    drawBugs(window, font);
}

void Board::drawGrid(sf::RenderWindow& window, const sf::Font& font) const {
    sf::RectangleShape line(sf::Vector2f(600, 2));
    line.setFillColor(sf::Color::Black);

    for (int i = 0; i <= 10; ++i) {
        line.setPosition(100, 100 + i * 40);
        window.draw(line);
    }

    line.setSize(sf::Vector2f(2, 400));
    for (int i = 0; i <= 10; ++i) {
        line.setPosition(100 + i * 60, 100);
        window.draw(line);
    }

    for (int x = 0; x < 10; x++) {
        sf::Text text(to_string(x), font, 12);
        text.setFillColor(sf::Color::Black);
        text.setPosition(100 + x * 60 + 25, 80);
        window.draw(text);
    }
    for (int y = 0; y < 10; y++) {
        sf::Text text(to_string(y), font, 12);
        text.setFillColor(sf::Color::Black);
        text.setPosition(80, 100 + y * 40 + 15);
        window.draw(text);
    }
}

void Board::drawBugs(sf::RenderWindow& window, const sf::Font& font) const {
    for (const auto& bug : bugs) {
        if (!bug->isAlive()) continue;

        Position pos = bug->getPosition();
        float radius = 15.0f + (bug->getSize() / 5.0f);
        sf::CircleShape shape(radius);

        if (dynamic_cast<Crawler*>(bug.get())) {
            shape.setFillColor(sf::Color::Red);
        } else if (dynamic_cast<Hopper*>(bug.get())) {
            shape.setFillColor(sf::Color::Blue);
        } else if (dynamic_cast<CrissCross*>(bug.get())) {
            shape.setFillColor(sf::Color::Green);
        }

        shape.setPosition(100 + pos.x * 60 - radius, 100 + pos.y * 40 - radius);
        window.draw(shape);

        sf::Text text(to_string(bug->getId()), font, 12);
        text.setFillColor(sf::Color::White);
        text.setPosition(100 + pos.x * 60 - 5, 100 + pos.y * 40 - 8);
        window.draw(text);

        sf::CircleShape directionIndicator(5);
        directionIndicator.setFillColor(sf::Color::Yellow);
        switch (bug->getDirection()) {
            case Direction::North:
                directionIndicator.setPosition(100 + pos.x * 60 - 2.5f, 100 + pos.y * 40 - 15);
                break;
            case Direction::East:
                directionIndicator.setPosition(100 + pos.x * 60 + 10, 100 + pos.y * 40 - 2.5f);
                break;
            case Direction::South:
                directionIndicator.setPosition(100 + pos.x * 60 - 2.5f, 100 + pos.y * 40 + 10);
                break;
            case Direction::West:
                directionIndicator.setPosition(100 + pos.x * 60 - 15, 100 + pos.y * 40 - 2.5f);
                break;
            default:
                break;
        }
        window.draw(directionIndicator);
    }
}
