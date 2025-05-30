#pragma once

#include "Entity.hpp"

class Pheromone : public Entity {
private:
    int strength;
    int radius;

public:
    Pheromone(Position pos, int s, int r)
        : Entity(pos), strength(s), radius(r) {}

    void decay();
    bool isGone() const;

    void update() override;

    int getRadius() const { return radius; }

    char getSymbol() const override { return '.'; }
    std::string getType() const override { return "Pheromone"; }
};