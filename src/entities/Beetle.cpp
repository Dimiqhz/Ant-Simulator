#include "../../include/entities/Beetle.hpp"
#include "../../include/entities/Ant.hpp"
#include "../../include/core/Grid.hpp"
#include "../../include/utils/Random.hpp"

extern Grid* globalGrid;

void Beetle::update() {
    if (!isAlive()) {
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
        globalGrid->moveEntity(shared_from_this(), newPos);
    }
}