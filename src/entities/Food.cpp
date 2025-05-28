#include "../../include/entities/Food.hpp"

int Food::take(int n) {
    int taken = std::min(units, n);
    units -= taken;
    return taken;
}

bool Food::isDepleted() const {
    return units <= 0;
}