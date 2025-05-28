#include "../../include/entities/Enemy.hpp"

void Enemy::damage(int d) {
    health -= d;
}

bool Enemy::isAlive() const {
    return health > 0;
}

int Enemy::getAttack() const {
    return attackPower;
}