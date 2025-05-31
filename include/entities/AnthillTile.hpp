#pragma once

#include "Entity.hpp"
#include "Anthill.hpp"
#include <memory>

class AnthillTile : public Entity {
private:
    std::shared_ptr<Anthill> parent;

public:
    AnthillTile(Position pos, std::shared_ptr<Anthill> parent)
        : Entity(pos), parent(std::move(parent)) {}

    std::string getType() const override { return "Anthill"; }
    char getSymbol() const override { return 'H'; }

    std::shared_ptr<Anthill> getParent() const { return parent; }

    void update() override {}
};