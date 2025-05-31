#include <algorithm>
#include <iostream>
#include <core/Grid.hpp>
#include "../../include/core/Grid.hpp"

#include <entities/Pheromone.hpp>

class Entity;

void Grid::draw() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (cells[y][x]) {
                std::cout << cells[y][x]->getSymbol() << ' ';
            } else if (pheromones[y][x]) {
                std::cout << pheromones[y][x]->getSymbol() << ' ';
            } else {
                std::cout << ". ";
            }
        }
        std::cout << '\n';
    }
}

void Grid::place(const std::shared_ptr<Entity>& entity) {
    if (!entity || !isInside(entity->getPosition())) return;

    const Position& pos = entity->getPosition();
    if (get(pos)) return;

    cells[pos.y][pos.x] = entity;
}

void Grid::placePheromone(const std::shared_ptr<Pheromone>& phero) {
    if (!phero || !isInside(phero->getPosition())) return;

    const Position& pos = phero->getPosition();
    pheromones[pos.y][pos.x] = phero;
}

std::shared_ptr<Pheromone> Grid::getPheromone(const Position& pos) const {
    if (!isInside(pos)) return nullptr;
    return pheromones[pos.y][pos.x];
}

std::vector<std::shared_ptr<Pheromone>> Grid::getAllPheromones() const {
    std::vector<std::shared_ptr<Pheromone>> all;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (pheromones[y][x]) {
                all.push_back(pheromones[y][x]);
            }
        }
    }
    return all;
}

void Grid::removePheromone(const Position& pos) {
    if (isInside(pos)) {
        pheromones[pos.y][pos.x] = nullptr;
    }
}

void Grid::removeEntity(const Position& pos) {
    if (isInside(pos)) {
        cells[pos.y][pos.x] = nullptr;
    }
}

void Grid::moveEntity(const std::shared_ptr<Entity>& entity, const Position& newPos) {
    if (!entity || !isInside(newPos)) return;

    const Position oldPos = entity->getPosition();
    if (oldPos == newPos) return;

    auto existing = get(newPos);

    if (existing && existing->getType() != "Food") {
        std::cerr << "[Grid] ОШИБКА: Позиция занята: " << newPos.toString() << " (" << existing->getType() << ")\n";
        return;
    }

    if (isInside(oldPos)) {
        clearCell(oldPos);
    }

    entity->setPosition(newPos);
    cells[newPos.y][newPos.x] = entity;
}

std::vector<std::shared_ptr<Entity>> Grid::getAllEntities() const {
    std::vector<std::shared_ptr<Entity>> all;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (cells[y][x]) {
                all.push_back(cells[y][x]);
            }
        }
    }
    return all;
}

std::vector<std::shared_ptr<Entity>> Grid::getEntitiesOfType(const std::string& type) const {
    std::vector<std::shared_ptr<Entity>> result;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            auto& entity = cells[y][x];
            if (entity && entity->getType() == type) {
                result.push_back(entity);
            }
        }
    }
    return result;
}

int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
}

void Grid::clearCell(const Position& pos) {
    if (isInside(pos)) {
        cells[pos.y][pos.x] = nullptr;
    }
}

std::vector<std::shared_ptr<Pheromone>> Grid::getPheromonesAround(const Position& center, int radius) const {
    std::vector<std::shared_ptr<Pheromone>> result;

    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            Position p = center.offset(dx, dy);
            if (!isInside(p)) continue;

            auto phero = pheromones[p.y][p.x];
            if (phero) result.push_back(phero);
        }
    }

    return result;
}

std::vector<std::shared_ptr<Entity>> Grid::getEntitiesAround(const Position& pos, int radius) {
    std::vector<std::shared_ptr<Entity>> result;

    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            Position p = pos.offset(dx, dy);
            if (isInside(p)) {
                auto entity = get(p);
                if (entity) {
                    result.push_back(entity);
                }
            }
        }
    }

    return result;
}