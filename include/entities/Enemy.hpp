#pragma once

#include "Entity.hpp"

class Enemy : public Entity {
protected:
    int health;
    int attackPower;

public:
    Enemy(Position pos, int hp, int atk)
        : Entity(pos), health(hp), attackPower(atk) {}

    void damage(int d);
    bool isAlive() const;
    int getAttack() const;

    virtual void update() = 0;
};