#include "../../include/entities/CigaretteButt.hpp"
#include "../../include/entities/Ant.hpp"
#include "../../include/core/Grid.hpp"

extern Grid* globalGrid;

void CigaretteButt::update() {
    Position pos = getPosition();

    for (int dx = -decayRadius; dx <= decayRadius; ++dx) {
        for (int dy = -decayRadius; dy <= decayRadius; ++dy) {
            if (dx == 0 && dy == 0) continue;
            Position adj = pos.offset(dx, dy);
            auto target = globalGrid->get(adj);
            if (target && target->getType().find("Ant") != std::string::npos) {
                auto ant = std::dynamic_pointer_cast<Ant>(target);
                if (ant) ant->damage(attackPower);
            }
        }
    }

    if (health > 0) --health;
    if (health <= 0) globalGrid->removeEntity(pos);
}