#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "arkanoid/box.hpp"
#include "arkanoid/brick.hpp"
#include "arkanoid/ball.hpp"
#include "arkanoid/paddle.hpp"

namespace arkanoid {

class GameBoard {
public:
    GameBoard(sf::Vector2f const& box_size, int level_num = 1);

    void update(float dt);
    void draw(sf::RenderWindow& window) const;

    const Box& box() const;
    Paddle& paddle();
    Ball& ball();
    const std::vector<Brick>& bricks() const;

private:
    Box box_;
    Paddle paddle_;
    Ball ball_;
    std::vector<Brick> bricks_;
};

} // namespace arkanoid
