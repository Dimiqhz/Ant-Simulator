#pragma once

#include "../core/Grid.hpp"
#include "../core/Position.hpp"
#include <memory>

class World {
private:
    Grid grid;
    int stepCount;

    void spawnWorkerAnt(const Position& center);
    void spawnWarriorAnt(const Position& center);
    void spawnFood();
    void spawnBeetle();
    void spawnCigaretteButt();

public:
    World(int width, int height);

    void update();
    void draw() const;
};