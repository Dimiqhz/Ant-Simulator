#pragma once

#include "Entity.hpp"

class Pheromone : public Entity {
private:
    int strength;
    int radius;
    std::string owner;
    int lifespan = 20;

public:
    Pheromone(Position pos, int s, int r, const std::string& own = "")
        : Entity(pos), strength(s), radius(r), owner(own) {}

    void decay();

    void update() override;

    bool isGone() const;

    int getStrength() const { return strength; }
    const std::string& getOwner() const { return owner; }

    int getRadius() const { return radius; }

    char getSymbol() const override { return '+'; }
    std::string getType() const override { return "Pheromone"; }
};