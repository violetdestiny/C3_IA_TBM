//
// Created by Ikram on 26/04/2025.
//
#include "SuperBug.h"
#include <iostream>

SuperBug::SuperBug(int id, int x, int y, Direction dir, int size)
    : Bug(id, x, y, dir, size) {
    shape.setRadius(20.f);
    shape.setFillColor(sf::Color::Magenta);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::White);
}

void SuperBug::move(Direction dir) {
    if (!alive) return;

    Position newPos = position;
    direction = dir;

    switch(dir) {
        case Direction::North: newPos.y--; break;
        case Direction::East:  newPos.x++; break;
        case Direction::South: newPos.y++; break;
        case Direction::West:  newPos.x--; break;
        default: break;
    }


    if (newPos.x >= 0 && newPos.x < 10 && newPos.y >= 0 && newPos.y < 10) {
        position = newPos;
        path.push_back(position);
    }
}
void SuperBug::move() {
    move(direction);
}
void SuperBug::draw(sf::RenderWindow& window) {
    if (!alive) return;
    shape.setPosition(position.x * 60.f + 30.f, position.y * 60.f + 30.f);
    window.draw(shape);
}

void SuperBug::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch(event.key.code) {
            case sf::Keyboard::Up:    move(Direction::North); break;
            case sf::Keyboard::Right:  move(Direction::East);  break;
            case sf::Keyboard::Down:   move(Direction::South); break;
            case sf::Keyboard::Left:   move(Direction::West);  break;
            default: break;
        }
    }
}