#include <algorithm>
#include <iostream>
#include <core/Grid.hpp>
#include "../../include/core/Grid.hpp"

class Entity;

void Grid::draw() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (cells[y][x]) {
                std::cout << cells[y][x]->getSymbol() << ' ';
            } else {
                std::cout << ". ";
            }
        }
        std::cout << '\n';
    }
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

Grid* globalGrid = nullptr;