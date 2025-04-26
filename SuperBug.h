//
// Created by ikram abbas on 25/04/2025.
//

#ifndef SUPERBUG_H
#define SUPERBUG_H

#include "Bug.h"
#include <SFML/Window/Keyboard.hpp>

class SuperBug : public Bug {
private:
    int kills = 0;

public:
    SuperBug(int id, int x, int y, Direction dir, int size)
        : Bug(id, x, y, dir, size) {}

    void move() override;
    void handleInput(sf::Keyboard::Key key);
    int getKills() const { return kills; }
    void addKill() { kills++; }
};

#endif // SUPERBUG_H