#pragma once

#include "Enemy.hpp"
#include "../core/Direction.hpp"

class Beetle : public Enemy {
private:
    Direction dir;

public:
    Beetle(Position pos, Direction d)
        : Enemy(pos, 80, 15), dir(d) {}

    Direction getDirection() const { return dir; }

    void update() override;

    char getSymbol() const override { return 'B'; }
    std::string getType() const override { return "Beetle"; }
};