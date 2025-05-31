#pragma once

#include "../core/Position.hpp"
#include <memory>
#include <string>

class Entity : public std::enable_shared_from_this<Entity> {
protected:
    Position position;
    bool alive = true;

public:
    explicit Entity(const Position& pos) : position(pos) {}
    virtual ~Entity() = default;

    const Position& getPosition() const { return position; }
    void setPosition(const Position& pos) { position = pos; }

    virtual bool isAlive() const { return alive; }
    virtual void update() = 0;

    virtual char getSymbol() const = 0;
    virtual std::string getType() const = 0;

    // using std::enable_shared_from_this<Entity>::shared_from_this;
};