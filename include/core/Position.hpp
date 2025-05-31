#pragma once

#include <compare>
#include <string>

struct Position {
    int x;
    int y;

    auto operator<=>(const Position&) const = default;

    std::string toString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

    Position offset(int dx, int dy) const {
        return Position{x + dx, y + dy};
    }

    int manhattanDistance(const Position& other) const {
        return std::abs(x - other.x) + std::abs(y - other.y);
    }
};