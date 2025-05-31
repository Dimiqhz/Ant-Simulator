#pragma once

#include "Ant.hpp"

class WarriorAnt : public Ant {
public:
    WarriorAnt(Position pos, Direction dir)
    : Ant(pos, dir, 10, 1, 3) {}

    void update() override;
    int getAttack() const { return 3; }

    char getSymbol() const override { return 'M'; }
    std::string getType() const override { return "WarriorAnt"; }
};