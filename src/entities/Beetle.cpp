#include "../../include/entities/Beetle.hpp"
#include "../../include/entities/Ant.hpp"
#include "../../include/core/Grid.hpp"
#include "../../include/utils/Random.hpp"
#include <iostream>
#include <memory>
#include "../include/Globals.hpp"

void Beetle::update() {
    // std::cout << "[DEBUG] Beetle::update() at " << position.x << "," << position.y << "\n";
    if (--lifetime <= 0) {
        globalGrid->removeEntity(getPosition());
        return;
    }

    Position pos = getPosition();

    for (auto [dx, dy] : {std::pair{-1,0}, {1,0}, {0,-1}, {0,1}}) {
        Position adj = pos.offset(dx, dy);
        auto target = globalGrid->get(adj);

        if (target && target->getType().find("Ant") != std::string::npos) {
            auto ant = std::dynamic_pointer_cast<Ant>(target);
            if (ant && ant->isAlive()) {
                ant->damage(attackPower);
                return;
            }
        }
    }

    std::vector<std::pair<int, int>> moves = {{0,-1}, {1,0}, {0,1}, {-1,0}};
    auto [dx, dy] = moves[Random::randint(0, 3)];
    Position newPos = pos.offset(dx, dy);

    if (globalGrid->isInside(newPos) && !globalGrid->get(newPos)) {
        auto beetlePtr = std::dynamic_pointer_cast<Beetle>(shared_from_this());
        if (beetlePtr) {
            globalGrid->moveEntity(beetlePtr, newPos);
        } else {
            std::cerr << "[ERROR] weak_from_this().lock() failed — объект разрушен\n";
        }
    }
}