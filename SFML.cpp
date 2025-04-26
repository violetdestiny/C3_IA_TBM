

//
// Created by Ikram on 26/04/2025.
//
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
#include <thread>

#include <SFML/Graphics.hpp>
#include "Crawler.h"
#include "Board.h"
#include "Hopper.h"
#include "CrissCross.h"
#include "SuperBug.h"
#include <iostream>
void runSFMLVisualization(Board& board) {
    const int tileSize = 60;
    const int gridSize = 10; // Assuming 10x10 grid based on your Board implementation
    const int windowWidth = gridSize * tileSize;
    const int windowHeight = gridSize * tileSize + 40; // Extra space for instructions

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Bug Simulation");
    sf::Event event;

    // Load textures
    sf::Texture crawlerTexture, hopperTexture, crissCrossTexture, superBugTexture;
    const std::string resourcePath = "resources/";

    if (!crawlerTexture.loadFromFile(resourcePath + "Crawler.png")) {
        throw std::runtime_error("Failed to load Crawler.png");
    }
    if (!hopperTexture.loadFromFile(resourcePath + "Hopper.png")) {
        throw std::runtime_error("Failed to load Hopper.png");
    }
    if (!crissCrossTexture.loadFromFile(resourcePath + "CrissCross.png")) {
        throw std::runtime_error("Failed to load CrissCross.png");
    }
    if (!superBugTexture.loadFromFile(resourcePath + "SuperBug.png")) {
        throw std::runtime_error("Failed to load SuperBug.png");
    }

    // Check if SuperBug exists and get its position
    SuperBug* superBug = board.getSuperBug();
    bool superBugExists = (superBug != nullptr);
    sf::Sprite superBugSprite;
    if (superBugExists) {
        superBugSprite.setTexture(superBugTexture);
        // Scale SuperBug to 80% of tile size
        float scale = 0.8f * tileSize / std::max(
            superBugTexture.getSize().x,
            superBugTexture.getSize().y
        );
        superBugSprite.setScale(scale, scale);
    }

    // Load font for instructions
    sf::Font font;
    if (!font.loadFromFile(resourcePath + "arial.ttf")) {
        std::cout << "Failed to load font\n"; // Replaced cerr with cout
    }

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle SuperBug controls if it exists
            if (superBugExists && event.type == sf::Event::KeyPressed) {
                Direction newDir = superBug->getDirection();
                bool moved = false;

                switch(event.key.code) {
                    case sf::Keyboard::Up:
                        newDir = Direction::North;
                        moved = true;
                        break;
                    case sf::Keyboard::Right:
                        newDir = Direction::East;
                        moved = true;
                        break;
                    case sf::Keyboard::Down:
                        newDir = Direction::South;
                        moved = true;
                        break;
                    case sf::Keyboard::Left:
                        newDir = Direction::West;
                        moved = true;
                        break;
                    case sf::Keyboard::Space:
                        // Fight at current position
                        board.handleSuperBugFights();
                        break;
                    case sf::Keyboard::T:  // Changed from M to T to match your tapBoard()
                        // Move all other bugs
                        board.tapBoard(); // Using tapBoard() instead of moveAll()
                        break;
                    default:
                        break;
                }

                if (moved) {
                    superBug->move(newDir);
                }
            }
        }

        window.clear(sf::Color::White);

        // Draw grid
        for (int x = 0; x <= windowWidth; x += tileSize) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(static_cast<float>(x), 0.f)),
                sf::Vertex(sf::Vector2f(static_cast<float>(x), static_cast<float>(windowHeight - 40)))
            };
            window.draw(line, 2, sf::Lines);
        }

        for (int y = 0; y <= windowHeight - 40; y += tileSize) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(0.f, static_cast<float>(y))),
                sf::Vertex(sf::Vector2f(static_cast<float>(windowWidth), static_cast<float>(y)))
            };
            window.draw(line, 2, sf::Lines);
        }

        // Draw all bugs except SuperBug
        for (const auto& bug : board.getBugs()) {
            if (bug->isAlive() && !dynamic_cast<SuperBug*>(bug.get())) {
                Position pos = bug->getPosition();
                sf::Sprite bugSprite;

                if (dynamic_cast<Crawler*>(bug.get())) {
                    bugSprite.setTexture(crawlerTexture);
                } else if (dynamic_cast<Hopper*>(bug.get())) {
                    bugSprite.setTexture(hopperTexture);
                } else if (dynamic_cast<CrissCross*>(bug.get())) {
                    bugSprite.setTexture(crissCrossTexture);
                }

                // Scale bug sprite to 80% of tile size
                float scale = 0.8f * tileSize / std::max(
                    bugSprite.getLocalBounds().width,
                    bugSprite.getLocalBounds().height
                );
                bugSprite.setScale(scale, scale);

                // Center the sprite in the grid cell
                float offsetX = (tileSize - bugSprite.getGlobalBounds().width) / 2.0f;
                float offsetY = (tileSize - bugSprite.getGlobalBounds().height) / 2.0f;

                bugSprite.setPosition(
                    static_cast<float>(pos.x * tileSize) + offsetX,
                    static_cast<float>(pos.y * tileSize) + offsetY
                );

                window.draw(bugSprite);
            }
        }

        // Draw SuperBug if it exists (on top of other bugs)
        if (superBugExists && superBug->isAlive()) {
            Position pos = superBug->getPosition();

            // Center the SuperBug in the grid cell
            float offsetX = (tileSize - superBugSprite.getGlobalBounds().width) / 2.0f;
            float offsetY = (tileSize - superBugSprite.getGlobalBounds().height) / 2.0f;

            superBugSprite.setPosition(
                static_cast<float>(pos.x * tileSize) + offsetX,
                static_cast<float>(pos.y * tileSize) + offsetY
            );
            window.draw(superBugSprite);
        }

        // Draw instructions if font loaded
        if (font.getInfo().family != "") {
            sf::Text instructions;
            instructions.setFont(font);

            if (superBugExists) {
                instructions.setString("Arrow Keys: Move SuperBug | Space: Fight | T: Tap board");
            } else {
                instructions.setString("No SuperBug detected - add one to enable controls");
            }

            instructions.setCharacterSize(20);
            instructions.setFillColor(sf::Color::Black);
            instructions.setPosition(10.f, static_cast<float>(windowHeight - 30));
            window.draw(instructions);

            // Draw SuperBug stats if it exists
            if (superBugExists) {
                sf::Text stats;
                stats.setFont(font);
                stats.setString("SuperBug - Kills: " + std::to_string(superBug->getKills()) +
                              " | Size: " + std::to_string(superBug->getSize()));
                stats.setCharacterSize(18);
                stats.setFillColor(sf::Color::Red);
                stats.setPosition(10.f, static_cast<float>(windowHeight - 60));
                window.draw(stats);
            }
        }

        window.display();
    }
}