#include "../../include/utils/Random.hpp"

std::mt19937 Random::engine(std::random_device{}());

int Random::randint(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}

int Random::chance(int percent) {
    return randint(1, 100) <= percent;
}