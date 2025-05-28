#pragma once

#include "Enemy.hpp"

class CigaretteButt : public Enemy {
private:
    int decayRadius;

public:
    CigaretteButt(Position pos)
        : Enemy(pos, 50, 10), decayRadius(1) {}

    void decay() { if (health > 0) --health; }

    int getRadius() const { return decayRadius; }

    void update() override;

    char getSymbol() const override { return 'X'; }
    std::string getType() const override { return "CigaretteButt"; }
};