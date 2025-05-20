#include <algorithm>

#include "arkanoid/game_board.hpp"
#include "arkanoid/level.hpp"
#include "arkanoid/collision_detector.hpp"
#include "arkanoid/resources_and_consts.hpp"

namespace arkanoid {

GameBoard::GameBoard(sf::Vector2u const& box_size, int level_num)
: box_({20.f, 20.f}, box_size, sf::Color::Black, sf::Color::White)
, paddle_(
    {100.f, consts::PaddleHeight},
    {box_.get_position().x + box_.get_size().x / 2.f,
    box_.get_position().y + box_.get_size().y - consts::OffsetBottom - consts::PaddleHeight / 2.f},
    consts::PaddleColor, //consts::gray,
    350.f)
, ball_(
    {box_.get_position().x + box_.get_size().x / 2.f,
    paddle_.get_position().y - consts::PaddleHeight / 2.f - consts::BallRadius - 1.f},
    consts::BallRadius,
    {0.f, 0.f},
    sf::Color::White)
{
    load_level(level_num);
}

void GameBoard::load_level(int level_num) {
    // Use the simplified load_level_pattern function
    bricks_ = level::load(
        level_num,
        //box_.get_position(),  // Box position
        {box_.left(), box_.top()},  // Box position
        box_.get_size(),      // Box size
        consts::OffsetLeft,          // Left padding
        consts::OffsetRight,         // Right padding
        consts::OffsetTop,           // Top padding
        consts::BrickHeight          // Brick height
    );
}

void GameBoard::update(float dt) {
    ball_.update(dt);
    paddle_.update(dt);
    // for (auto& brick : bricks_)
    //     brick->update(dt);
}

void GameBoard::reset_ball_paddle() {
    ball_.reset();
    paddle_.reset();
}

void GameBoard::launch_ball() {
    ball_.launch();
}

void GameBoard::move_paddle_left() {
    paddle_.move_left();
}

void GameBoard::move_paddle_right() {
    paddle_.move_right();
}

bool GameBoard::is_all_bricks_cleared() const {
    return std::all_of(bricks_.begin(), bricks_.end(), [](const auto& brick) {
        return brick->was_hit();//is_destroyed();
    });
}

void GameBoard::draw(sf::RenderWindow& window) const {
    box_.draw(window);
    paddle_.draw(window);
    ball_.draw(window);
    for (const auto& brick : bricks_)
        brick->draw(window);
}

void GameBoard::reset(int level)
{
    paddle_.reset();
    ball_.reset();
    load_level(level);
}

collision_detector::CollisionResult GameBoard::handle_collision() {
    // ─── Paddle Collision ─────────────────────────────────────
    const float box_left = box_.get_position().x;
    const float box_right = box_left + box_.get_size().x;
    auto paddle_pos = paddle_.get_position();
    const float half_width = paddle_.get_size().x / 2.f;

    if (paddle_pos.x - half_width < box_left)
        paddle_pos.x = box_left + half_width;
    else if (paddle_pos.x + half_width > box_right)
        paddle_pos.x = box_right - half_width;

    paddle_.set_position(paddle_pos);

    // ─── Ball vs Box ───────────────────────────────────────────
    if (collision_detector::handle_box_collision(ball_, box_)) {
        ball_.reset();
        paddle_.reset();

        return collision_detector::CollisionResult::BallFell;
    }

    // ─── Ball vs Paddle ───────────────────────────────────────
    collision_detector::handle_paddle_collision(ball_, paddle_);

    // ─── Ball vs Bricks ───────────────────────────────────────
    for (auto& brick : bricks_) {
        if (!brick->was_hit()) {
            collision_detector::handle_brick_collision(ball_, *brick);
            if (brick->was_hit()) {
                return collision_detector::CollisionResult::BrickHit;
            }
        }
    }

    if (is_all_bricks_cleared()) {
        return collision_detector::CollisionResult::LevelComplete;
    }

    return collision_detector::CollisionResult::NoChange;
}


} // namespace arkanoid