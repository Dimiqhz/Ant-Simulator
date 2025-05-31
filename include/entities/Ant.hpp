#pragma once

#include "Entity.hpp"
#include <core/Direction.hpp>
#include <memory>

class Ant : public Entity {
protected:
    Direction direction;
    int health;
    int age;
    int speed;
    int attackPower;

public:
    Ant(Position pos, Direction dir, int health, int speed, int attack = 0)
        : Entity(pos), direction(dir), health(health), speed(speed), age(0), attackPower(attack) {}

    Direction getDirection() const { return direction; }
    void setDirection(Direction d) { direction = d; }

    void ageStep() {
        ++age;
        health -= 1;
        if (age > 200) health = 0;
    }

    void damage(int amount) { health -= amount; }
    void heal(int amount) { health += amount; }
    int getAttack() const { return attackPower; }

    bool isAlive() const { return health > 0; }

    virtual void update() = 0;
};