#include "../../include/world/World.hpp"
#include <iostream>
#include "../../include/core/Grid.hpp"
#include "../../include/entities/WorkerAnt.hpp"
#include "../../include/entities/WarriorAnt.hpp"
#include "../../include/entities/Anthill.hpp"
#include "../../include/entities/AnthillTile.hpp"
#include "../../include/entities/Food.hpp"
#include "../../include/entities/Beetle.hpp"
#include "../../include/entities/CigaretteButt.hpp"
#include "../../include/entities/Pheromone.hpp"
#include "../../include/utils/Random.hpp"
#include "../include/Globals.hpp"

World::World(int width, int height) : grid(width, height), stepCount(0) {
    globalGrid = &grid;
    globalWorld = this;

    std::vector<Position> hillArea = {
        {width / 2,     height / 2},
        {width / 2 + 1, height / 2},
        {width / 2,     height / 2 + 1},
        {width / 2 + 1, height / 2 + 1}
    };

    anthill = std::make_shared<Anthill>(hillArea);
    ::anthill = anthill;

    for (const auto& pos : hillArea) {
        auto tile = std::make_shared<AnthillTile>(pos, anthill);
        grid.place(tile);
    }

    entities.push_back(anthill);

    Position base = anthill->getArea()[0];
    for (int i = 0; i < 3; ++i) spawnWorkerAnt(base);
    for (int i = 0; i < 2; ++i) spawnWarriorAnt(base);
}

void World::spawnWorkerAnt(const Position& center) {
    Direction dir = static_cast<Direction>(Random::randint(0, 3));
    Position pos = center.offset(Random::randint(-1, 1), Random::randint(-1, 1));

    if (anthill) {
        for (const auto& cell : anthill->getArea()) {
            if (pos == cell) return;
        }
    }

    if (grid.isInside(pos) && !grid.get(pos)) {
        grid.place(std::make_shared<WorkerAnt>(pos, dir));
        anthill->increasePopulation();
    }
}

void World::spawnWarriorAnt(const Position& center) {
    Direction dir = static_cast<Direction>(Random::randint(0, 3));
    Position pos = center.offset(Random::randint(-1, 1), Random::randint(-1, 1));

    if (anthill) {
        for (const auto& cell : anthill->getArea()) {
            if (pos == cell) return;
        }
    }

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
    auto fieldEntities = grid.getAllEntities();
    std::vector<std::shared_ptr<Entity>> toRemove;

    for (auto& entity : fieldEntities) {
        if (entity && entity->isAlive()) {
            entity->update();
        } else if (entity) {
            toRemove.push_back(entity);
        }
    }

    for (auto& e : toRemove) {
        grid.removeEntity(e->getPosition());
    }

    if (stepCount % 15 == 0 && Random::chance(50)) spawnBeetle();
    if (stepCount % 20 == 0 && Random::chance(50)) spawnCigaretteButt();

    auto pheromones = grid.getAllPheromones();
    for (auto& phero : pheromones) {
        if (!phero) continue;
        phero->update();
        if (phero->isGone()) {
            grid.removePheromone(phero->getPosition());
        }
    }

    for (auto& entity : entities) {
        if (entity && entity->isAlive()) {
            entity->update();
        }
    }

    if (anthill && anthill->getFoodCount() >= 10 && Random::chance(30)) {
        if (Random::chance(50)) spawnWorkerAnt(anthill->getPosition());
        else spawnWarriorAnt(anthill->getPosition());
        anthill->consumeFood(10);
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
            if (obj && obj->getType() == "Food") currentFood++;
        }
    }

    if (currentFood < maxFoodCount) spawnFood();
    if (Random::randint(0, 19) == 0) spawnBeetle();
    if (Random::randint(0, 29) == 0) spawnCigaretteButt();
    if (stepCount % 20 == 0 && anthill) anthill->grow();
}

void World::render() const {
    draw();
}

void World::getStats() {
    int workers = 0, warriors = 0, foodCount = 0, pheromones = 0, beetles = 0, butts = 0;

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

    int totalAnts = workers + warriors;

    std::cout << "Шаг симуляции: " << stepCount << "\n";
    std::cout << "Муравьи: " << totalAnts << " (Рабочие: " << workers << ", Воины: " << warriors << ")\n";
    std::cout << "Пища на поле: " << foodCount << "\n";
    std::cout << "Феромоны: " << pheromones << "\n";
    std::cout << "Жуки: " << beetles << "\n";
    std::cout << "Окурки: " << butts << "\n";

    if (anthill) {
        if (anthill->isDestroyed()) {
            std::cout << "[SIMULATION] Муравейник уничтожен. Конец симуляции.\n";
            exit(0);
        }
        std::cout << "Собрано пищи в муравейнике: " << anthill->getFoodCount() << "\n";
        std::cout << "Возраст муравейника: " << anthill->getAge() << "\n";
        std::cout << "Популяция: " << anthill->getPopulation() << "\n";
    }

    std::cout << "Живых сущностей на поле: " << grid.getAllEntities().size() << "\n";
}