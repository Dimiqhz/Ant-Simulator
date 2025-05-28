#include "../../include/entities/WorkerAnt.hpp"
#include "../../include/entities/Food.hpp"
#include "../../include/entities/Anthill.hpp"
#include "../../include/entities/Pheromone.hpp"
#include "../../include/core/Grid.hpp"
#include "../../include/utils/Random.hpp"

extern Grid* globalGrid;

WorkerAnt::WorkerAnt(Position pos, Direction dir)
    : Ant(pos, dir, 100, 1) {}

void WorkerAnt::pickUpFood() { carryingFood = true; }
void WorkerAnt::dropFood() { carryingFood = false; }
bool WorkerAnt::hasFood() const { return carryingFood; }

void WorkerAnt::update() {
    ageStep();
    if (!isAlive()) return;

    globalGrid->place(std::make_shared<Pheromone>(getPosition(), 5, 1));

    for (auto [dx, dy] : {std::pair{-1,0}, {1,0}, {0,-1}, {0,1}}) {
        Position adj = position.offset(dx, dy);
        auto obj = globalGrid->get(adj);

        if (!hasFood() && obj && obj->getType() == "Food") {
            auto food = std::dynamic_pointer_cast<Food>(obj);
            if (food && !food->isDepleted()) {
                pickUpFood();
                food->take(1);
                globalGrid->moveEntity(shared_from_this(), adj);
                return;
            }
        }

        if (hasFood() && obj && obj->getType() == "Anthill") {
            auto anthill = std::dynamic_pointer_cast<Anthill>(obj);
            dropFood();
            anthill->addFood(1);
            heal(30);
            return;
        }
    }

    std::vector<std::pair<int, int>> moves = {{0,-1}, {1,0}, {0,1}, {-1,0}};
    std::shuffle(moves.begin(), moves.end(), Random::engine);

    for (auto [dx, dy] : moves) {
        Position newPos = position.offset(dx, dy);
        if (globalGrid->isInside(newPos) && !globalGrid->get(newPos)) {
            globalGrid->moveEntity(shared_from_this(), newPos);
            return;
        }
    }
}

char WorkerAnt::getSymbol() const {
    return carryingFood ? 'C' : 'W';
}

std::string WorkerAnt::getType() const {
    return "WorkerAnt";
}