#include "../../include/world/World.hpp"

#include <iostream>

#include "../../include/core/Grid.hpp"
#include "../../include/entities/WorkerAnt.hpp"
#include "../../include/entities/WarriorAnt.hpp"
#include "../../include/entities/Anthill.hpp"
#include "../../include/entities/Food.hpp"
#include "../../include/entities/Beetle.hpp"
#include "../../include/entities/CigaretteButt.hpp"
#include "../../include/entities/Pheromone.hpp"
#include "../../include/utils/Random.hpp"

extern Grid* globalGrid;

World::World(int width, int height) : grid(width, height), stepCount(0) {
    globalGrid = &grid;

    Position hillPos = {width / 2, height / 2};
    auto hill = std::make_shared<Anthill>(hillPos);
    anthill = std::make_shared<Anthill>(hillPos);
    grid.place(hill);

    for (int i = 0; i < 3; ++i) {
        spawnWorkerAnt(hillPos);
    }
    for (int i = 0; i < 2; ++i) {
        spawnWarriorAnt(hillPos);
    }
}

void World::spawnWorkerAnt(const Position& center) {
    Direction dir = static_cast<Direction>(Random::randint(0, 3));
    Position pos = center.offset(Random::randint(-1, 1), Random::randint(-1, 1));
    if (grid.isInside(pos) && !grid.get(pos)) {
        grid.place(std::make_shared<WorkerAnt>(pos, dir));
        anthill->increasePopulation();
    }
}

void World::spawnWarriorAnt(const Position& center) {
    Direction dir = static_cast<Direction>(Random::randint(0, 3));
    Position pos = center.offset(Random::randint(-1, 1), Random::randint(-1, 1));
    if (grid.isInside(pos) && !grid.get(pos)) {
        grid.place(std::make_shared<WarriorAnt>(pos, dir));
        anthill->increasePopulation();
    }
}

void World::spawnFood() {
    Position pos{Random::randint(0, grid.getWidth() - 1), Random::randint(0, grid.getHeight() - 1)};
    if (!grid.get(pos)) {
        grid.place(std::make_shared<Food>(pos));
    }
}

void World::spawnBeetle() {
    Position pos{Random::randint(0, grid.getWidth() - 1), Random::randint(0, grid.getHeight() - 1)};
    if (!grid.get(pos)) {
        Direction dir = static_cast<Direction>(Random::randint(0, 3));
        grid.place(std::make_shared<Beetle>(pos, dir));
    }
}

void World::spawnCigaretteButt() {
    Position pos{Random::randint(0, grid.getWidth() - 1), Random::randint(0, grid.getHeight() - 1)};
    if (!grid.get(pos)) {
        grid.place(std::make_shared<CigaretteButt>(pos));
    }
}

void World::update() {
    stepCount++;

    auto entities = grid.getAllEntities();
    for (auto& entity : entities) {
        if (entity->isAlive()) {
            entity->update();
        } else {
            grid.remove(entity->getPosition());
        }
    }

    if (stepCount % 10 == 0) {
        spawnFood();
    }

    if (stepCount % 15 == 0 && Random::chance(50)) {
        spawnBeetle();
    }

    if (stepCount % 20 == 0 && Random::chance(50)) {
        spawnCigaretteButt();
    }

    auto pheromones = grid.getEntitiesOfType("Pheromone");
    for (auto& phero : pheromones) {
        auto ph = std::dynamic_pointer_cast<Pheromone>(phero);
        ph->decay();
        if (!ph->isAlive()) {
            grid.remove(ph->getPosition());
        }
    }

    auto anthills = grid.getEntitiesOfType("Anthill");
    for (auto& hillEntity : anthills) {
        auto hill = std::dynamic_pointer_cast<Anthill>(hillEntity);
        if (hill->getFoodCount() >= 10 && Random::chance(30)) {
            if (Random::chance(50)) {
                spawnWorkerAnt(hill->getPosition());
            } else {
                spawnWarriorAnt(hill->getPosition());
            }
            hill->consumeFood(10);
        }
    }
}

void World::draw() const {
    grid.draw();
}

void World::runStep() {
    ++stepCount;
    update();

    const int maxFoodCount = 5;
    int currentFood = 0;

    for (int y = 0; y < grid.getHeight(); ++y) {
        for (int x = 0; x < grid.getWidth(); ++x) {
            auto obj = grid.get({x, y});
            if (obj && obj->getType() == "Food") {
                ++currentFood;
            }
        }
    }

    if (currentFood < maxFoodCount) {
        spawnFood();
    }

    if (Random::randint(0, 19) == 0) {
        spawnBeetle();
    }

    if (Random::randint(0, 29) == 0) {
        spawnCigaretteButt();
    }

    if (stepCount % 20 == 0) {
        anthill->grow();
    }
}

void World::render() const {
    draw();
}

void World::getStats() {
    int workers = 0;
    int warriors = 0;
    int foodCount = 0;
    int pheromones = 0;
    int beetles = 0;
    int butts = 0;
    int totalAnts = 0;

    for (int y = 0; y < grid.getHeight(); ++y) {
        for (int x = 0; x < grid.getWidth(); ++x) {
            auto entity = grid.get({x, y});
            if (!entity) continue;

            if (entity->getType() == "WorkerAnt") workers++;
            else if (entity->getType() == "WarriorAnt") warriors++;
            else if (entity->getType() == "Food") foodCount++;
            else if (entity->getType() == "Pheromone") pheromones++;
            else if (entity->getType() == "Beetle") beetles++;
            else if (entity->getType() == "CigaretteButt") butts++;
        }
    }

    totalAnts = workers + warriors;

    std::cout << "Шаг симуляции: " << stepCount << "\n";
    std::cout << "Муравьи: " << totalAnts << " (Рабочие: " << workers << ", Воины: " << warriors << ")\n";
    std::cout << "Пища на поле: " << foodCount << "\n";
    std::cout << "Феромоны: " << pheromones << "\n";
    std::cout << "Жуки: " << beetles << "\n";
    std::cout << "Окурки: " << butts << "\n";
    std::cout << "Собрано пищи в муравейнике: " << anthill->getFoodCount() << "\n";
    std::cout << "Возраст муравейника: " << anthill->getAge() << "\n";
    std::cout << "Популяция: " << anthill->getPopulation() << "\n";
}