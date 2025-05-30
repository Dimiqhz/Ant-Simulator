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
    int getFoodCount() const { return foodStored; }
    void consumeFood(int amount) { foodStored = std::max(0, foodStored - amount); }
    void grow() { ++age; }

    int getAge() const { return age; }
    int getPopulation() const { return population; }
    void increasePopulation(int n = 1) { population += n; }

    char getSymbol() const override { return 'H'; }
    std::string getType() const override { return "Anthill"; }
};