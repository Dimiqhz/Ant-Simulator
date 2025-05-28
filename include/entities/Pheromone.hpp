#pragma once

#include "Entity.hpp"

class Pheromone : public Entity {
private:
    int strength;
    int radius;
    int lifetime = 10;

public:
    Pheromone(Position pos, int str, int rad)
        : Entity(pos), strength(str), radius(rad) {}

    void decay();
    bool isGone() const;

    char getSymbol() const override { return '~'; }
    std::string getType() const override { return "Pheromone"; }
    bool isAlive() const override { return lifetime > 0; }
};