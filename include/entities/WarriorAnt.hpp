#pragma once

#include "Ant.hpp"

class WarriorAnt : public Ant {
private:
    int attack;

public:
    WarriorAnt(Position pos, Direction dir)
        : Ant(pos, dir, 120, 1), attack(20) {}

    int getAttack() const { return attack; }

    void update() override;

    char getSymbol() const override { return 'M'; }
    std::string getType() const override { return "WarriorAnt"; }
};