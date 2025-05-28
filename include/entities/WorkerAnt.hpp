#pragma once
#include "Ant.hpp"

class WorkerAnt : public Ant {
private:
    bool carryingFood = false;
public:
    WorkerAnt(Position pos, Direction dir);
    void pickUpFood();
    void dropFood();
    bool hasFood() const;
    void update() override;
    char getSymbol() const override;
    std::string getType() const override;
};