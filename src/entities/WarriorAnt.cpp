#include "../../include/entities/WarriorAnt.hpp"
#include "../../include/entities/Enemy.hpp"
#include "../../include/core/Grid.hpp"
#include "../../include/utils/Random.hpp"
#include "../../include/entities/Anthill.hpp"
#include "../include/Globals.hpp"
#include <iostream>
#include <optional>

std::optional<Position> findNearestEnemy(const Position& from, int radius) {
    std::optional<Position> targetPos;
    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            Position adj = from.offset(dx, dy);
            if (!globalGrid->isInside(adj)) continue;
            auto entity = globalGrid->get(adj);
            if (!entity) continue;
            std::string type = entity->getType();
            if (type == "Beetle" || type == "CigaretteButt") {
                targetPos = adj;
                return targetPos;
            }
        }
    }
    return std::nullopt;
}

void WarriorAnt::update() {
    ageStep();
    if (!isAlive()) return;

    if (!anthill || !globalGrid) return;

    auto self = std::dynamic_pointer_cast<WarriorAnt>(shared_from_this());
    if (!self) return;

    globalGrid->placePheromone(std::make_shared<Pheromone>(getPosition(), 10, 3, "Warrior"));

    for (const auto& pos : anthill->getArea()) {
        if (getPosition() == pos) {
            heal(999);
            return;
        }
    }

    Position pos = getPosition();

    for (auto [dx, dy] : {std::pair{-1,0}, {1,0}, {0,-1}, {0,1}}) {
        Position adj = pos.offset(dx, dy);
        auto target = globalGrid->get(adj);

        if (target && (target->getType() == "Beetle" || target->getType() == "CigaretteButt")) {
            auto enemy = std::dynamic_pointer_cast<Enemy>(target);
            if (enemy && enemy->isAlive()) {
                enemy->damage(getAttack());
                if (enemy->getType() == "CigaretteButt") {
                    this->damage(enemy->getAttack());
                }
                return;
            }
        }
    }

    auto entities = globalGrid->getEntitiesAround(pos, 4);
    Position targetPos = pos;
    int minDist = 999;

    for (auto& e : entities) {
        if (!e) continue;
        if (e->getType() == "Beetle" || e->getType() == "CigaretteButt") {
            int dist = pos.manhattanDistance(e->getPosition());
            if (dist < minDist) {
                minDist = dist;
                targetPos = e->getPosition();
            }
        }
    }

    if (targetPos != pos) {
        std::vector<std::pair<int, int>> moves = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
        std::shuffle(moves.begin(), moves.end(), Random::engine);

        Position bestMove = pos;
        int bestDist = minDist;

        for (auto [dx, dy] : moves) {
            Position newPos = pos.offset(dx, dy);
            if (!globalGrid->isInside(newPos) || globalGrid->get(newPos)) continue;

            int dist = newPos.manhattanDistance(targetPos);
            if (dist < bestDist) {
                bestMove = newPos;
                bestDist = dist;
            }
        }

        if (bestMove != pos) {
            globalGrid->moveEntity(self, bestMove);
            return;
        }
    }

    std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    std::shuffle(directions.begin(), directions.end(), Random::engine);
    for (auto [dx, dy] : directions) {
        Position newPos = pos.offset(dx, dy);
        if (globalGrid->isInside(newPos) && !globalGrid->get(newPos)) {
            globalGrid->moveEntity(self, newPos);
            return;
        }
    }
}