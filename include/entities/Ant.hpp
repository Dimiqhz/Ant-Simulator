#pragma once

#include "Entity.hpp"
#include <random>

class Ant : public Entity {
protected:
    Direction direction;
    int health;
    int age;
    int speed;

public:
    Ant(Position pos, Direction dir, int hp, int spd)
        : Entity(pos), direction(dir), health(hp), age(0), speed(spd) {}

    Direction getDirection() const { return direction; }
    void setDirection(Direction d) { direction = d; }

    void ageStep() { ++age; }
    void damage(int amount) { health -= amount; }
    void heal(int amount) { health += amount; }

    bool isAlive() const { return health > 0; }

    virtual void update() = 0;
};