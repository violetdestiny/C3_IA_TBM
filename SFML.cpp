

//
// Created by Ikram on 26/04/2025.
//
#include <SFML/Graphics.hpp>
#include "Crawler.h"
#include "Board.h"
#include "Hopper.h"
#include "CrissCross.h"
#include "SuperBug.h"
#include <iostream>
using namespace std;
using namespace sf;

void runSFMLVisualization(Board& board) {
    const int tileSize = 60;
    const int gridSize = 10;
    const int windowWidth = gridSize * tileSize;
    const int windowHeight = gridSize * tileSize + 100;

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Bug Simulation");
    Event event;

    Texture crawlerTexture, hopperTexture, crissCrossTexture, superBugTexture;
    const string resourcePath = "resources/";

    if (!crawlerTexture.loadFromFile(resourcePath + "Crawler.png")) {
        throw runtime_error("Failed to load Crawler.png");
    }
    if (!hopperTexture.loadFromFile(resourcePath + "Hopper.png")) {
        throw runtime_error("Failed to load Hopper.png");
    }
    if (!crissCrossTexture.loadFromFile(resourcePath + "CrissCross.png")) {
        throw runtime_error("Failed to load CrissCross.png");
    }
    if (!superBugTexture.loadFromFile(resourcePath + "SuperBug.png")) {
        throw runtime_error("Failed to load SuperBug.png");
    }

    SuperBug* superBug = board.getSuperBug();
    bool superBugExists = (superBug != nullptr);
    Sprite superBugSprite;
    if (superBugExists) {
        superBugSprite.setTexture(superBugTexture);
        float scale = 0.8f * tileSize / max(
            superBugTexture.getSize().x,
            superBugTexture.getSize().y
        );
        superBugSprite.setScale(scale, scale);
    }

    Font font;
    if (!font.loadFromFile(resourcePath + "arial.ttf")) {
        cout << "Failed to load font\n";
    }

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (superBugExists && event.type == Event::KeyPressed) {
                Direction newDir = superBug->getDirection();
                bool moved = false;

                switch(event.key.code) {
                    case Keyboard::Up:
                        newDir = Direction::North;
                        moved = true;
                        break;
                    case Keyboard::Right:
                        newDir = Direction::East;
                        moved = true;
                        break;
                    case Keyboard::Down:
                        newDir = Direction::South;
                        moved = true;
                        break;
                    case Keyboard::Left:
                        newDir = Direction::West;
                        moved = true;
                        break;
                    case Keyboard::Space:
                        board.handleSuperBugFights();
                        break;
                    case Keyboard::T:
                        board.tapBoard();
                        break;
                    default:
                        break;
                }

                if (moved) {
                    superBug->move(newDir);
                }
            }
        }

        window.clear(Color::White);

        RectangleShape gridBackground(Vector2f(windowWidth, windowHeight - 100));
        gridBackground.setFillColor(Color::White);
        gridBackground.setPosition(0, 0);
        window.draw(gridBackground);

        Color purple(128, 0, 128);
        for (int x = 0; x <= windowWidth; x += tileSize) {
            Vertex line[] = {
                Vertex(Vector2f(static_cast<float>(x), 0.f), purple),
                Vertex(Vector2f(static_cast<float>(x), static_cast<float>(windowHeight - 100)), purple)
            };
            window.draw(line, 2, Lines);
        }

        for (int y = 0; y <= windowHeight - 100; y += tileSize) {
            Vertex line[] = {
                Vertex(Vector2f(0.f, static_cast<float>(y)), purple),
                Vertex(Vector2f(static_cast<float>(windowWidth), static_cast<float>(y)), purple)
            };
            window.draw(line, 2, Lines);
        }

        for (const auto& bug : board.getBugs()) {
            if (bug->isAlive() && !dynamic_cast<SuperBug*>(bug.get())) {
                Position pos = bug->getPosition();
                Sprite bugSprite;

                if (dynamic_cast<Crawler*>(bug.get())) {
                    bugSprite.setTexture(crawlerTexture);
                } else if (dynamic_cast<Hopper*>(bug.get())) {
                    bugSprite.setTexture(hopperTexture);
                } else if (dynamic_cast<CrissCross*>(bug.get())) {
                    bugSprite.setTexture(crissCrossTexture);
                }

                float scale = 0.8f * tileSize / max(
                    bugSprite.getLocalBounds().width,
                    bugSprite.getLocalBounds().height
                );
                bugSprite.setScale(scale, scale);

                float offsetX = (tileSize - bugSprite.getGlobalBounds().width) / 2.0f;
                float offsetY = (tileSize - bugSprite.getGlobalBounds().height) / 2.0f;

                bugSprite.setPosition(
                    static_cast<float>(pos.x * tileSize) + offsetX,
                    static_cast<float>(pos.y * tileSize) + offsetY
                );

                window.draw(bugSprite);
            }
        }

        if (superBugExists && superBug->isAlive()) {
            Position pos = superBug->getPosition();

            float offsetX = (tileSize - superBugSprite.getGlobalBounds().width) / 2.0f;
            float offsetY = (tileSize - superBugSprite.getGlobalBounds().height) / 2.0f;

            superBugSprite.setPosition(
                static_cast<float>(pos.x * tileSize) + offsetX,
                static_cast<float>(pos.y * tileSize) + offsetY
            );
            window.draw(superBugSprite);
        }

        if (font.getInfo().family != "") {
            Text instructions;
            instructions.setFont(font);
            instructions.setCharacterSize(16);
            instructions.setFillColor(Color::Black);

            if (superBugExists) {
                instructions.setString("Arrow Keys: Move SuperBug | Space: Kill | T: Tap board");
            } else {
                instructions.setString("No SuperBug ;(");
            }

            instructions.setPosition(10.f, static_cast<float>(windowHeight - 80));
            window.draw(instructions);

            if (superBugExists) {
                Text stats;
                stats.setFont(font);
                stats.setString("SuperBug - Kills: " + to_string(superBug->getKills()) );
                stats.setCharacterSize(16);
                stats.setFillColor(Color::Black);
                stats.setPosition(10.f, static_cast<float>(windowHeight - 50));
                window.draw(stats);
            }
        }

        window.display();
    }
}
// #include <thread>
// #include <SFML/Graphics.hpp>
// #include "Crawler.h"
// #include "Board.h"
// #include "Hopper.h"
// #include "CrissCross.h"
// #include "SFML.h"
// void runSFMLVisualization(Board& board) {
//     sf::RenderWindow window(sf::VideoMode({800, 600}), "Bug Simulation");
//     sf::Event event;
//
//     while (window.isOpen()) {
//
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//         }
//
//         window.clear(sf::Color::White);
//
//
//         for (int x = 0; x <= 800; x += 60) {
//             sf::Vertex line[] = {
//                 sf::Vertex(sf::Vector2f(static_cast<float>(x), 0.f)),
//                 sf::Vertex(sf::Vector2f(static_cast<float>(x), 600.f))
//             };
//             window.draw(line, 2, sf::Lines);
//         }
//
//         for (int y = 0; y <= 600; y += 60) {
//             sf::Vertex line[] = {
//                 sf::Vertex(sf::Vector2f(0.f, static_cast<float>(y))),
//                 sf::Vertex(sf::Vector2f(800.f, static_cast<float>(y)))
//             };
//             window.draw(line, 2, sf::Lines);
//         }
//
//
//         for (const auto& bug : board.getBugs()) {
//             if (bug->isAlive()) {
//                 Position pos = bug->getPosition();
//                 sf::CircleShape bugShape(15.f);
//
//                 if (dynamic_cast<Crawler*>(bug.get())) {
//                     bugShape.setFillColor(sf::Color::Red);
//                 } else if (dynamic_cast<Hopper*>(bug.get())) {
//                     bugShape.setFillColor(sf::Color::Green);
//                 } else if (dynamic_cast<CrissCross*>(bug.get())) {
//                     bugShape.setFillColor(sf::Color::Blue);
//                 }
//
//                 bugShape.setPosition({
//                     static_cast<float>(pos.x * 60 + 30),
//                     static_cast<float>(pos.y * 60 + 30)
//                 });
//                 window.draw(bugShape);
//             }
//         }
//
//         window.display();
//     }
// }
