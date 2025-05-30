#include "../include/world/World.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <map>

int main(int argc, char** argv) {
    int width = 8;
    int height = 8;
    bool autoMode = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.starts_with("--width=")) {
            width = std::stoi(arg.substr(8));
        } else if (arg.starts_with("--height=")) {
            height = std::stoi(arg.substr(9));
        } else if (arg == "--auto") {
            autoMode = true;
        } else {
            std::cerr << "Неизвестный аргумент: " << arg << "\n";
        }
    }

    World world(width, height);
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