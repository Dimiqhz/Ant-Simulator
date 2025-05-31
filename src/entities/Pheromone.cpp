#include "../../include/entities/Pheromone.hpp"
#include "../../include/core/Grid.hpp"
#include "../include/Globals.hpp"

void Pheromone::decay() {
    if (strength > 0) --strength;
}

bool Pheromone::isGone() const {
    return strength <= 0;
}

void Pheromone::update() {
    lifespan--;
    if (lifespan <= 0) alive = false;
}