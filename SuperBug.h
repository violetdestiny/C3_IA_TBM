//
// Created by Ikram on 26/04/2025.
//
#ifndef SUPERBUG_H
#define SUPERBUG_H

#include "Bug.h"
#include <SFML/Graphics.hpp>
class SuperBug : public Bug {
private:
    int kills = 0;
    sf::CircleShape shape;

public:
    SuperBug(int id, int x, int y);
    SuperBug(int id, int x, int y, Direction dir, int size);
    void move() override;
    void move(Direction dir);
    void draw(sf::RenderWindow& window);
    void handleInput(const sf::Event& event);

    void addKill() { kills++; }
    int getKills() const { return kills; }
};


#endif // SUPERBUG_H
