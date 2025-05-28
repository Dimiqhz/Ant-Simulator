#pragma once

#include <string>

enum class Direction {
    North,
    East,
    South,
    West
};


inline std::string to_string(Direction dir) {
    switch (dir) {
        case Direction::North: return "↑";
        case Direction::East:  return "→";
        case Direction::South: return "↓";
        case Direction::West:  return "←";
        default:               return "?";
    }
}

inline std::pair<int, int> directionOffset(Direction dir) {
    switch (dir) {
        case Direction::North: return {0, -1};
        case Direction::East:  return {1, 0};
        case Direction::South: return {0, 1};
        case Direction::West:  return {-1, 0};
        default:               return {0, 0};
    }
}