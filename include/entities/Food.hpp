#pragma once

#include "Entity.hpp"

class Food : public Entity {
private:
    int units;

public:
    Food(Position pos, int amount) : Entity(pos), units(amount) {}

    int take(int n);
    bool isDepleted() const;


    char getSymbol() const override { return '@'; }
    std::string getType() const override { return "Food"; }
};