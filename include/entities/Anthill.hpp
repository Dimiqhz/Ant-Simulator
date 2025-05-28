#pragma once

#include "Entity.hpp"

class Anthill : public Entity {
private:
    int age;
    int population;
    int foodStored;

public:
    Anthill(Position pos) : Entity(pos), age(0), population(0), foodStored(0) {}

    void addFood(int n) { foodStored += n; }
    void grow() { ++age; }

    char getSymbol() const override { return 'H'; }
    std::string getType() const override { return "Anthill"; }
};