#pragma once

#include "Entity.hpp"

class Food : public Entity {
private:
    int units;
    int quantity;

public:
    Food(Position pos) : Entity(pos), quantity(5) {}

    int take(int n);
    bool isDepleted() const;


    char getSymbol() const override { return '@'; }
    std::string getType() const override { return "Food"; }
};