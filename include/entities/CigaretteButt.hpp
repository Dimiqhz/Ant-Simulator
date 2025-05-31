#pragma once

#include "Enemy.hpp"

class CigaretteButt : public Enemy {
private:
    int decayRadius;

public:
    CigaretteButt(Position pos)
        : Enemy(pos, 50, 10), decayRadius(1) {}

    int getRadius() const { return decayRadius; }

    void update() override;

    char getSymbol() const override { return '~'; }
    std::string getType() const override { return "CigaretteButt"; }
};