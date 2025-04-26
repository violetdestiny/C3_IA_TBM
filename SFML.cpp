

//
// Created by Ikram on 26/04/2025.
//
#include <thread>
#include <SFML/Graphics.hpp>
#include "Crawler.h"
#include "Board.h"
#include "Hopper.h"
#include "CrissCross.h"
#include "SFML.h"
void runSFMLVisualization(Board& board) {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Bug Simulation");
    sf::Event event;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);


        for (int x = 0; x <= 800; x += 60) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(static_cast<float>(x), 0.f)),
                sf::Vertex(sf::Vector2f(static_cast<float>(x), 600.f))
            };
            window.draw(line, 2, sf::Lines);
        }

        for (int y = 0; y <= 600; y += 60) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(0.f, static_cast<float>(y))),
                sf::Vertex(sf::Vector2f(800.f, static_cast<float>(y)))
            };
            window.draw(line, 2, sf::Lines);
        }


        for (const auto& bug : board.getBugs()) {
            if (bug->isAlive()) {
                Position pos = bug->getPosition();
                sf::CircleShape bugShape(15.f);

                if (dynamic_cast<Crawler*>(bug.get())) {
                    bugShape.setFillColor(sf::Color::Red);
                } else if (dynamic_cast<Hopper*>(bug.get())) {
                    bugShape.setFillColor(sf::Color::Green);
                } else if (dynamic_cast<CrissCross*>(bug.get())) {
                    bugShape.setFillColor(sf::Color::Blue);
                }

                bugShape.setPosition({
                    static_cast<float>(pos.x * 60 + 30),
                    static_cast<float>(pos.y * 60 + 30)
                });
                window.draw(bugShape);
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
// #include "SuperBug.h"
// #include "SFML.h"
//
// void runSFMLVisualization(Board& board) {
//     sf::RenderWindow window(sf::VideoMode({800, 600}), "Bug Simulation");
//     sf::Event event;
//
//
//     sf::Texture crawlerTexture, hopperTexture, crissCrossTexture, superBugTexture;
//     const std::string resourcePath = "C:/Users/Tahar/CLionProjects/CA3_IA_TBM/resources/";
//
//     if (!crawlerTexture.loadFromFile(resourcePath + "Crawler.png")) {
//         throw std::runtime_error("Failed to load Crawler.png");
//     }
//     if (!hopperTexture.loadFromFile(resourcePath + "Hopper.png")) {
//         throw std::runtime_error("Failed to load Hopper.png");
//     }
//     if (!crissCrossTexture.loadFromFile(resourcePath + "CrissCross.png")) {
//         throw std::runtime_error("Failed to load CrissCross.png");
//     }
//     if (!superBugTexture.loadFromFile(resourcePath + "SuperBug.png")) {
//         throw std::runtime_error("Failed to load SuperBug.png");
//     }
//
//     while (window.isOpen()) {
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
//                 sf::Sprite bugSprite;
//
//                 if (dynamic_cast<Crawler*>(bug.get())) {
//                     bugSprite.setTexture(crawlerTexture);
//                 } else if (dynamic_cast<Hopper*>(bug.get())) {
//                     bugSprite.setTexture(hopperTexture);
//                 } else if (dynamic_cast<CrissCross*>(bug.get())) {
//                     bugSprite.setTexture(crissCrossTexture);
//                 } else if (dynamic_cast<SuperBug*>(bug.get())) {
//                     bugSprite.setTexture(superBugTexture);
//                 }
//
//                 bugSprite.setPosition(
//                     static_cast<float>(pos.x * 60),
//                     static_cast<float>(pos.y * 60)
//                 );
//
//                 window.draw(bugSprite);
//             }
//         }
//
//         window.display();
//     }
// }