#pragma once

#include "arkanoid/ball.hpp"
#include "arkanoid/box.hpp"
#include "arkanoid/brick.hpp"
#include "arkanoid/paddle.hpp"

namespace arkanoid
{

namespace collision_detector
{
    
enum class CollisionResult {
    NoChange,
    BallFell,
    BrickHit,
    LevelComplete
};

void handle_particle_collision(Ball& a, Ball& b);
bool handle_box_collision(Ball& particle, const Box& box);
void handle_brick_collision(Ball& ball, Brick& brick);
void handle_paddle_collision(Ball& ball, const Paddle& paddle);

namespace util {
    sf::Vector2f normalize(const sf::Vector2f& v);
    float dot(const sf::Vector2f& a, const sf::Vector2f& b);
    float length(const sf::Vector2f& v);
    float clamp_ball_angle(float angle_deg);
}

} // namespace collision_detector

} // namespace arkanoid