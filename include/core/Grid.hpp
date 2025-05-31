#pragma once

#include <vector>
#include <memory>
#include "Position.hpp"
#include <entities/Pheromone.hpp>

class Entity;
class Pheromone;

class Grid {
private:
    int width, height;
    std::vector<std::vector<std::shared_ptr<Entity>>> cells;
    std::vector<std::vector<std::shared_ptr<Pheromone>>> pheromones;

public:
    Grid(int w, int h)
        : width(w), height(h),
          cells(h, std::vector<std::shared_ptr<Entity>>(w, nullptr)),
          pheromones(h, std::vector<std::shared_ptr<Pheromone>>(w, nullptr)) {}

    bool isInside(const Position& pos) const {
        return pos.x >= 0 && pos.y >= 0 && pos.x < width && pos.y < height;
    }

    std::shared_ptr<Entity> get(const Position& pos) const {
        if (!isInside(pos)) return nullptr;
        return cells[pos.y][pos.x];
    }

    std::shared_ptr<Pheromone> getPheromone(const Position& pos) const;

    void place(const std::shared_ptr<Entity>& entity);
    void placePheromone(const std::shared_ptr<Pheromone>& phero);
    void removeEntity(const Position& pos);
    void moveEntity(const std::shared_ptr<Entity>& entity, const Position& newPos);
    void clearCell(const Position& pos);

    void draw() const;

    int getWidth() const;
    int getHeight() const;

    std::vector<std::shared_ptr<Entity>> getAllEntities() const;
    std::vector<std::shared_ptr<Entity>> getEntitiesOfType(const std::string& type) const;
    std::vector<std::shared_ptr<Pheromone>> getAllPheromones() const;
    void removePheromone(const Position& pos);

    std::vector<std::shared_ptr<Pheromone>> getPheromonesAround(const Position& center, int radius) const;
    std::vector<std::shared_ptr<Entity>> getEntitiesAround(const Position& pos, int radius);
};