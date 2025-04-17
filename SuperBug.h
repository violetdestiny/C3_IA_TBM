//
// Created by Ikram on 26/04/2025.
//
#ifndef SUPERBUG_H
#define SUPERBUG_H

#include "Bug.h"
#include <SFML/Graphics.hpp>

class SuperBug : public Bug {
private:
    sf::CircleShape shape;
    static const int SUPER_SIZE = 25;

public:
    SuperBug(int id, int x, int y);
    void move(Direction dir);
    void move() override {}
    void draw(sf::RenderWindow& window);
    void handleInput(const sf::Event& event);
};

#endif // SUPERBUG_H
