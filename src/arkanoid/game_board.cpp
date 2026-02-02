#include <algorithm>

#include "arkanoid/game_board.hpp"
#include "arkanoid/level.hpp"
#include "arkanoid/collision_detector.hpp"
#include "arkanoid/resources_and_consts.hpp"

namespace arkanoid {

GameBoard::GameBoard(sf::Vector2u const& box_size)//, int level_num)
: box_(consts::ArkanoidBoxPosition, box_size, sf::Color::Black, sf::Color::White)
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
, is_ball_attached_to_paddle_{true}
{
    //load_level(level_num);
}

// void GameBoard::load_level(int level_num) {
//     // Use the simplified load_level_pattern function
//     bricks_ = level::load(
//         level_num,
//         //box_.get_position(),  // Box position
//         {box_.left(), box_.top()},  // Box position
//         box_.get_size(),      // Box size
//         consts::OffsetLeft,          // Left padding
//         consts::OffsetRight,         // Right padding
//         consts::OffsetTop,           // Top padding
//         consts::BrickHeight          // Brick height
//     );
//     level_num_ = level_num;
// }

void GameBoard::load_level(const LevelData& level_data) {
    bricks_.clear();
    // You might also want to reset paddle/ball, etc., here if needed

    // Use the utility to build bricks from the level data
    bricks_ = level::load(
        level_data,
        //box_.get_position(),  // Box position
        {box_.left(), box_.top()},  // Box position
        box_.get_size()     // Box size
    );
}

void GameBoard::update(float dt) {
    ball_.update(dt);
    paddle_.update(dt);
    // for (auto& brick : bricks_)
    //     brick->update(dt);
    if (is_ball_attached_to_paddle_) {
        ball_.set_position( {paddle_.get_position().x, 
            paddle_.get_position().y - consts::PaddleHeight / 2.f - consts::BallRadius - 1.f} );
    }
}


void GameBoard::reset_ball_paddle() {
    ball_.reset();
    paddle_.reset();
    is_ball_attached_to_paddle_ = true;
}

void GameBoard::launch_ball() {
    ball_.launch();
    is_ball_attached_to_paddle_ = false;
}

void GameBoard::move_paddle_left() {
    paddle_.move_left();
}

void GameBoard::move_paddle_right() {
    paddle_.move_right();
}

bool GameBoard::is_all_bricks_cleared() const {
    return std::all_of(bricks_.begin(), bricks_.end(),
        [](const auto& brick) { return brick->is_indestructible(); });
}

void GameBoard::draw(sf::RenderWindow& window) const {
    box_.draw(window);
    paddle_.draw(window);
    ball_.draw(window);
    for (const auto& brick : bricks_)
        brick->draw(window);
}

// void GameBoard::reset(int level)
// {
//     paddle_.reset();
//     ball_.reset();
//     load_level(level);
//     is_ball_attached_to_paddle_ = true;
// }

void GameBoard::reset(const LevelData& level_data)
{
    paddle_.reset();
    ball_.reset();
    is_ball_attached_to_paddle_ = true;
    // Clear any existing bricks or state
    bricks_.clear();
    // You might also want to reset paddle/ball, etc., here if needed

    // Use the utility to build bricks from the level data
    bricks_ = level::load(
        level_data,
        //box_.get_position(),  // Box position
        {box_.left(), box_.top()},  // Box position
        box_.get_size()      // Box size
    );

    // Optionally reset other state (score, lives, etc.)
}

collision_detector::CollisionInfo GameBoard::handle_collision(int level_num) {//collision_detector::CollisionResult
    // ─── Paddle Collision ─────────────────────────────────────
    const float box_left = box_.get_position().x;
    const float box_right = box_left + box_.get_size().x;
    auto paddle_pos = paddle_.get_position();
    const float half_width = paddle_.get_size().x / 2.f;

    if (paddle_pos.x - half_width - 3.f < box_left)
        paddle_pos.x = box_left + half_width + 3.f;
    else if (paddle_pos.x + half_width + 3.f > box_right)
        paddle_pos.x = box_right - half_width - 3.f; // - (bricks_outline thickness + box thickness)

    paddle_.set_position(paddle_pos);

    // ─── Ball vs Box ───────────────────────────────────────────
    if (collision_detector::handle_box_collision(ball_, box_)) {
        ball_.reset();
        paddle_.reset();

        //return collision_detector::CollisionResult::BallFell;
        return {collision_detector::CollisionResult::BallFell, 0};
    }

    // ─── Ball vs Paddle ───────────────────────────────────────
    if (!is_ball_attached_to_paddle_) {
        collision_detector::handle_paddle_collision(ball_, paddle_);
    

        // ─── Ball vs Bricks ───────────────────────────────────────
        // for (auto& brick : bricks_) {
        //     if (!brick->is_destroyed()) {//was_hit()
        //         collision_detector::handle_brick_collision(ball_, *brick);
        //         if (brick->is_destroyed()) {//was_hit()
        //             return collision_detector::CollisionResult::BrickHit;
        //         }
        //     }
        // }
        for (auto it = bricks_.begin(); it != bricks_.end(); ++it) {
            if (collision_detector::handle_brick_collision(ball_, **it)) {

                const int gained = (*it)->score(level_num);

                if (!(*it)->is_indestructible()) {
                    it = bricks_.erase(it); // actually destroys the brick
                }

                return { collision_detector::CollisionResult::BrickHit, gained };
            }
        }
    }

    if (is_all_bricks_cleared()) {
        //return collision_detector::CollisionResult::LevelComplete;
        return {collision_detector::CollisionResult::LevelComplete, 0};
    }

    //return collision_detector::CollisionResult::NoChange;
    return {collision_detector::CollisionResult::NoChange, 0};
    
}


} // namespace arkanoid