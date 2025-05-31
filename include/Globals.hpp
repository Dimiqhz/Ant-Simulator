#pragma once

#include <memory>
#include "core/Grid.hpp"

class World;
class Anthill;

inline Grid* globalGrid = nullptr;
inline World* globalWorld = nullptr;
inline std::shared_ptr<Anthill> anthill = nullptr;