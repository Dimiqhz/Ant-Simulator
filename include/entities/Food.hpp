#include <string>

#include "Entity.hpp"

class Food : public Entity {
private:
    int units;

public:
    Food(Position pos) : Entity(pos), units(5) {}

    int take(int n);
    bool isDepleted() const;

    char getSymbol() const override { return '@'; }
    std::string getType() const override { return "Food"; }
    void update() override {}
};
