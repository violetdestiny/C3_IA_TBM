//
// Created by ikram abbas on 26/04/2025.
//
#include "Board.h"
#include <SFML/Graphics.hpp>
#include "Crawler.h"
#include "Hopper.h"
#include "CrissCross.h"
using namespace sf;
using namespace std;
using namespace std;
void runSFMLSimulation(Board& board)
{
    sf::Texture crawlerTexture, hopperTexture, wallHuggerTexture, superBugTexture;

    if (!crawlerTexture.loadFromFile("Crawler.png") ||
        !hopperTexture.loadFromFile("Hopper.png") ||
        !wallHuggerTexture.loadFromFile("WallHugger.png") ||
        !superBugTexture.loadFromFile("SuperBug.png")) {
        throw std::runtime_error("Failed to load one or more bug textures.");
        }

    const int cellSize = 60;
    const int gridSize = 10;

    RenderWindow window(VideoMode(gridSize * cellSize, gridSize * cellSize), "Bug Battle - SFML");
    window.setFramerateLimit(10);

    vector<RectangleShape> rectangles;
    vector<CircleShape> bugShapes;
    vector<Text> bugTexts;

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        throw runtime_error("Could not load font");
    }

    // CHECKer board
    int i = 0;
    for (int x = 0; x < gridSize; x++) {
        for (int y = 0; y < gridSize; y++) {
            RectangleShape rect(Vector2f(cellSize, cellSize));
            rect.setFillColor(i%2==0 ? Color(240, 240, 240) : Color(200, 200, 200));
            i++;
            rect.setPosition(Vector2f(x*cellSize, y*cellSize));
            rectangles.push_back(rect);
        }
        i++;
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        board.tapBoard();

        if (event.type == sf::Event::KeyPressed) {
            if (board.getSuperBug()) {
                board.getSuperBug()->handleInput(event.key.code);
            }
        }

        // Bug stufff
        bugShapes.clear();
        bugTexts.clear();
        window.clear();

        // Draw grid
        for (RectangleShape &rect : rectangles) {
            window.draw(rect);
        }

        // Draw bugs
        for (const Bug* bug : board.getAllBugs()) {
            if (!bug->isAlive()) continue;

            sf::Sprite sprite;
            Position pos = bug->getPosition();

            std::string type = bug->getType();
            if (type == "Crawler") {
                sprite.setTexture(crawlerTexture);
            } else if (type == "Hopper") {
                sprite.setTexture(hopperTexture);
            } else if (type == "WallHugger") {
                sprite.setTexture(wallHuggerTexture);
            } else if (type == "SuperBug") {
                sprite.setTexture(superBugTexture);
            }

            sprite.setScale(1.f, 1.f);  // Doesn't scale because I made the sprites 60x60
            sprite.setPosition(pos.x * cellSize, pos.y * cellSize);  // Align top-left of sprite with top-left of cell

            window.draw(sprite);

            // sf::Text bugIdText;
            // bugIdText.setFont(font);
            // bugIdText.setCharacterSize(14);
            // bugIdText.setFillColor(sf::Color::White);
            // bugIdText.setString(std::to_string(bug->getId()));
            // bugIdText.setPosition(pos.x * cellSize + 20, pos.y * cellSize + 10);
            // window.draw(bugIdText);
        }

        window.display();


        // Draw grid
        for (RectangleShape &rect : rectangles) {
            window.draw(rect);
        }

        // Draw bugs
        for (CircleShape &bug : bugShapes) {
            window.draw(bug);
        }

        // Draw da text
        for (Text &text : bugTexts) {
            window.draw(text);
        }


        if (board.isGameOver()) {
            sleep(seconds(2));
            window.close();
        }
    }
}