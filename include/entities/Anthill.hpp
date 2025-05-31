#pragma once

#include "Entity.hpp"
#include <vector>
#include <utils/Random.hpp>
#include "Globals.hpp"
#include "../../include/world/World.hpp"

class Anthill : public Entity {
private:
    std::vector<Position> area;
    int age;
    int population;
    int foodStored;
    int health = 100;

public:
    const std::vector<Position>& getArea() const { return area; }

    std::vector<Position> hillPositions = {
        Position{4, 4}, Position{5, 4}, Position{4, 5}, Position{5, 5}
    };

    Anthill(const std::vector<Position>& areaPositions)
        : Entity(areaPositions[0]), area(areaPositions), age(0), population(0), foodStored(0) {}

    void addFood(int n) { foodStored += n; }
    int getFoodCount() const { return foodStored; }
    void consumeFood(int amount) { foodStored = std::max(0, foodStored - amount); }
    void grow() { ++age; }

    int getAge() const { return age; }
    int getPopulation() const { return population; }
    void increasePopulation(int n = 1) { population += n; }

    char getSymbol() const override { return 'H'; }
    std::string getType() const override { return "Anthill"; }

    void update() override;

    int getHealth() const { return health; }
    void decreaseHealth(int amount) { health = std::max(0, health - amount); }
    void increaseHealth(int amount) { health = std::min(100, health + amount); }
    bool isDestroyed() const { return health <= 0; }
};
