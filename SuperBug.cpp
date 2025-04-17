//
// Created by ikram abbas on 25/04/2025.
//
#include "SuperBug.h"
#include <iostream>

void SuperBug::move() {

}

void SuperBug::handleInput(sf::Keyboard::Key key) {
    Position newPos = position;

    switch(key) {
        case sf::Keyboard::Key::Up:
            newPos.y = std::max(0, position.y - 1);
        direction = Direction::North;
        break;
        case sf::Keyboard::Key::Right:
            newPos.x = std::min(9, position.x + 1);
        direction = Direction::East;
        break;
        case sf::Keyboard::Key::Down:
            newPos.y = std::min(9, position.y + 1);
        direction = Direction::South;
        break;
        case sf::Keyboard::Key::Left:
            newPos.x = std::max(0, position.x - 1);
        direction = Direction::West;
        break;
        default:
            return;
    }

    setPosition(newPos);
}