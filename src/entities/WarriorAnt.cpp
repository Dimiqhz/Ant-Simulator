#include "../../include/entities/WarriorAnt.hpp"
#include "../../include/entities/Enemy.hpp"
#include "../../include/core/Grid.hpp"
#include "../../include/utils/Random.hpp"

extern Grid* globalGrid;

void WarriorAnt::update() {
    ageStep();
    if (!isAlive()) return;

    Position pos = getPosition();

    for (auto [dx, dy] : {std::pair{-1,0}, {1,0}, {0,-1}, {0,1}}) {
        Position adj = pos.offset(dx, dy);
        auto target = globalGrid->get(adj);

        if (target && (target->getType() == "Beetle" || target->getType() == "CigaretteButt")) {
            auto enemy = std::dynamic_pointer_cast<Enemy>(target);
            if (enemy && enemy->isAlive()) {
                enemy->damage(getAttack());
                return;
            }
        }
    }

    std::vector<std::pair<int, int>> moves = {{0,-1}, {1,0}, {0,1}, {-1,0}};
    std::shuffle(moves.begin(), moves.end(), Random::engine);

    for (auto [dx, dy] : moves) {
        Position newPos = pos.offset(dx, dy);
        if (globalGrid->isInside(newPos) && !globalGrid->get(newPos)) {
            globalGrid->moveEntity(shared_from_this(), newPos);
            return;
        }
    }
}