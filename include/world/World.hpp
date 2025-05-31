#pragma once

#include <Globals.hpp>

#include "../core/Grid.hpp"
#include "../core/Position.hpp"
#include <memory>
#include <entities/Anthill.hpp>

class World {
private:
    Grid grid;
    int stepCount;
    std::shared_ptr<Anthill> anthill;
    std::vector<std::shared_ptr<Entity>> entities;

    void spawnFood();
    void spawnBeetle();
    void spawnCigaretteButt();

public:
    World(int width, int height);

    void update();
    void draw() const;

    void init();

    void runStep();
    void render() const;
    void getStats();
    int getStepCount() const { return stepCount; }

    void spawnWorkerAnt(const Position& center);
    void spawnWarriorAnt(const Position& center);

};
