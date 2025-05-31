#include "../../include/entities/Anthill.hpp"

#include <iostream>

#include "../../include/Globals.hpp"

void Anthill::update() {
    ++age;
    std::cout << "[Anthill] Tick #" << age << ", food: " << foodStored << "\n";
    if (foodStored >= 10 && Random::chance(30)) {
        std::cout << "[Anthill] Spawning ant...\n";
        consumeFood(10);
        Position center = area[0];
        if (Random::chance(50))
            globalWorld->spawnWorkerAnt(center);
        else
            globalWorld->spawnWarriorAnt(center);
        consumeFood(10);
    }
}