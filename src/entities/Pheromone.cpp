#include "../../include/entities/Pheromone.hpp"
#include "../../include/core/Grid.hpp"

extern Grid* globalGrid;

void Pheromone::decay() {
    if (strength > 0) --strength;
}

bool Pheromone::isGone() const {
    return strength <= 0;
}

void Pheromone::update() {
    decay();
    if (isGone()) {
        globalGrid->removeEntity(getPosition());
    }
}