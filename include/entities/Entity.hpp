#pragma once

#include "../core/Position.hpp"
#include "../core/Direction.hpp"
#include <string>

class Entity : public std::enable_shared_from_this<Entity>{
protected:
    Position position;

public:
    explicit Entity(Position pos) : position(pos) {}
    virtual ~Entity() = default;

    virtual char getSymbol() const = 0;
    virtual std::string getType() const = 0;

    const Position& getPosition() const;
    void setPosition(const Position& pos);

    virtual bool isAlive() const { return true; }
    virtual void update() {}
};