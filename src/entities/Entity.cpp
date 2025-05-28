#include "../../include/entities/Entity.hpp"

const Position& Entity::getPosition() const {
    return position;
}

void Entity::setPosition(const Position& pos) {
    position = pos;
}