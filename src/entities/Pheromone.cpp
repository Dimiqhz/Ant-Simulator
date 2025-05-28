#include "../../include/entities/Pheromone.hpp"

void Pheromone::decay() {
    if (strength > 0) --strength;
}

bool Pheromone::isGone() const {
    return strength <= 0;
}