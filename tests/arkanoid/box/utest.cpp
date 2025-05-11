#include "arkanoid/box/game.hpp"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    box::Game game;
    game.run();
    return 0;
}
