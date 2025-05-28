#pragma once
#include <random>

class Random {
public:
    static std::mt19937 engine;

    static int randint(int min, int max);
    static int chance(int percent);
};