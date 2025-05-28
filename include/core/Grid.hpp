#pragma once

#include "../entities/Entity.hpp"
#include <vector>
#include <memory>
#include <optional>
#include <string>

class Grid {
private:
    int width;
    int height;
    std::vector<std::vector<std::shared_ptr<Entity>>> cells;

public:

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    std::vector<std::shared_ptr<Entity>> getAllEntities() const;

    std::vector<std::shared_ptr<Entity>> getEntitiesOfType(const std::string& type) const;

    void remove(const Position& pos) { removeEntity(pos); }

    Grid(int w, int h) : width(w), height(h), cells(h, std::vector<std::shared_ptr<Entity>>(w, nullptr)) {}

    bool isInside(const Position& pos) const {
        return pos.x >= 0 && pos.y >= 0 && pos.x < width && pos.y < height;
    }

    void place(const std::shared_ptr<Entity>& entity) {
        if (isInside(entity->getPosition())) {
            cells[entity->getPosition().y][entity->getPosition().x] = entity;
        }
    }

    std::shared_ptr<Entity> get(const Position& pos) const {
        if (!isInside(pos)) return nullptr;
        return cells[pos.y][pos.x];
    }

    void clearCell(const Position& pos) {
        if (isInside(pos)) {
            cells[pos.y][pos.x] = nullptr;
        }
    }

    void moveEntity(const std::shared_ptr<Entity>& entity, const Position& newPos) {
        if (!isInside(newPos)) return;
        clearCell(entity->getPosition());
        entity->setPosition(newPos);
        place(entity);
    }

    void draw() const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    std::vector<std::shared_ptr<Entity>> getAllEntities() const;
    std::vector<std::shared_ptr<Entity>> getEntitiesOfType(const std::string& type) const;

    void remove(const Position& pos);
    void removeEntity(const Position& pos) { remove(pos); } // alias
};