#include "../../include/entities/WorkerAnt.hpp"
#include "../../include/entities/Food.hpp"
#include "../../include/entities/Anthill.hpp"
#include "../../include/entities/Pheromone.hpp"
#include "../../include/core/Grid.hpp"
#include "../../include/utils/Random.hpp"
#include "../include/Globals.hpp"
#include <iostream>
#include <core/Direction.hpp>

WorkerAnt::WorkerAnt(Position pos, Direction dir)
    : Ant(pos, dir, 100, 1) {}

void WorkerAnt::pickUpFood() { carryingFood = true; }
void WorkerAnt::dropFood() { carryingFood = false; }
bool WorkerAnt::hasFood() const { return carryingFood; }

void WorkerAnt::update() {
    if (!isAlive()) return;
    ageStep();
    if (!isAlive() || !globalGrid || !anthill) return;

    auto self = std::dynamic_pointer_cast<WorkerAnt>(shared_from_this());
    if (!self) return;

    int strength = hasFood() ? 30 : 20;
    int radius = hasFood() ? 2 : 1;
    std::string owner = hasFood() ? "WorkerWithFood" : "WorkerWithoutFood";
    globalGrid->placePheromone(std::make_shared<Pheromone>(getPosition(), strength, radius, owner));

    auto current = globalGrid->get(getPosition());
    if (!hasFood() && current && current->getType() == "Food") {
        auto food = std::dynamic_pointer_cast<Food>(current);
        if (food && !food->isDepleted()) {
            pickUpFood();
            food->take(1);
            if (food->isDepleted()) {
                globalGrid->removeEntity(getPosition());
            }
            return;
        }
    }

    for (const auto& pos : anthill->getArea()) {
        if (getPosition() == pos) {
            if (hasFood()) {
                dropFood();
                anthill->addFood(1);
                heal(30);
            } else {
                heal(999);
            }
            return;
        }
    }

    std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    std::shuffle(directions.begin(), directions.end(), Random::engine);

    if (!hasFood()) {
        for (auto [dx, dy] : directions) {
            Position adj = position.offset(dx, dy);
            auto obj = globalGrid->get(adj);
            if (obj && obj->getType() == "Food") {
                auto food = std::dynamic_pointer_cast<Food>(obj);
                if (food && !food->isDepleted()) {
                    globalGrid->moveEntity(self, adj);
                    pickUpFood();
                    food->take(1);
                    if (food->isDepleted()) {
                        globalGrid->removeEntity(adj);
                    }
                    return;
                }
            }
        }

        auto nearby = globalGrid->getPheromonesAround(getPosition(), 3);
        Position bestMove = position;
        int maxScore = -1;

        for (auto& ph : nearby) {
            if (!ph || ph->getOwner() != "WorkerWithFood") continue;
            int dist = getPosition().manhattanDistance(ph->getPosition());
            int score = ph->getStrength() - dist;
            if (score > maxScore && !globalGrid->get(ph->getPosition())) {
                maxScore = score;
                bestMove = ph->getPosition();
            }
        }

        if (bestMove != position) {
            globalGrid->moveEntity(self, bestMove);
            return;
        }

    } else {
        bool inOrNearAnthill = false;
        for (const auto& hillPos : anthill->getArea()) {
            if (getPosition() == hillPos) {
                inOrNearAnthill = true;
                break;
            }
            for (auto [dx, dy] : directions) {
                if (getPosition() == hillPos.offset(dx, dy)) {
                    inOrNearAnthill = true;
                    break;
                }
            }
            if (inOrNearAnthill) break;
        }

        if (inOrNearAnthill) {
            if (hasFood()) {
                dropFood();
                anthill->addFood(1);
                heal(30);
            } else {
                heal(999);
            }
            return;
        }

        auto nearby = globalGrid->getPheromonesAround(getPosition(), 3);
        Position bestMove = position;
        int maxScore = -1;

        for (auto& ph : nearby) {
            if (!ph || ph->getOwner() != "WorkerWithoutFood") continue;
            int dist = getPosition().manhattanDistance(ph->getPosition());
            int score = ph->getStrength() - dist;
            if (score > maxScore && !globalGrid->get(ph->getPosition())) {
                maxScore = score;
                bestMove = ph->getPosition();
            }
        }

        if (bestMove != position) {
            globalGrid->moveEntity(self, bestMove);
            return;
        }
    }

    for (auto [dx, dy] : directions) {
        Position newPos = position.offset(dx, dy);
        if (globalGrid->isInside(newPos) && !globalGrid->get(newPos)) {
            globalGrid->moveEntity(self, newPos);
            return;
        }
    }
}

char WorkerAnt::getSymbol() const {
    return carryingFood ? 'C' : 'W';
}

std::string WorkerAnt::getType() const {
    return "WorkerAnt";
}