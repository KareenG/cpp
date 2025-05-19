#pragma once

#include <vector>

#include "arkanoid/ball.hpp"
#include "arkanoid/paddle.hpp"
#include "arkanoid/box.hpp"
#include "arkanoid/brick.hpp"
#include "arkanoid/collision_detector.hpp"

namespace arkanoid {

class GameBoard {
public:
    GameBoard(sf::Vector2u const& box_size, int level_num = 1);

    void update(float dt);
    void reset_ball_paddle();
    void launch_ball();
    void move_paddle_left();
    void move_paddle_right();

    void draw(sf::RenderWindow& window) const;

    bool is_all_bricks_cleared() const;
    void reset(int level_num = 1);

    collision_detector::CollisionResult handle_collision();

private:
    void load_level(int level_num = 1);

private:
    Box box_;
    Paddle paddle_;
    Ball ball_;
    std::vector<std::unique_ptr<Brick>> bricks_;
};

} // namespace arkanoid
