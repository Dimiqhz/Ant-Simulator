#include "../include/world/World.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

int main(int argc, char** argv) {
    bool autoMode = (argc > 1 && std::string(argv[1]) == "--auto");

    World world(20, 20);
    std::string input;

    while (true) {
        world.render();

        if (autoMode) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } else {
            std::cout << "Нажмите ENTER для продолжения или введите \"quit\" / \"stats\"\n>>> ";
            std::getline(std::cin, input);
            if (input == "quit") break;
            if (input == "stats") {
                world.getStats();
                continue;
            }
        }

        world.runStep();
    }

    return 0;
}