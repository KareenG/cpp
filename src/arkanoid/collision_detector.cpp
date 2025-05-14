#include <cmath>

#include "arkanoid/collision_detector.hpp"

namespace arkanoid
{

namespace collision_detector
{

namespace util {

    sf::Vector2f normalize(const sf::Vector2f& v)
    {
        float len = std::sqrt(v.x * v.x + v.y * v.y);
        return len == 0 ? sf::Vector2f(0.f, 0.f) : v / len;
    }

    float dot(const sf::Vector2f& a, const sf::Vector2f& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    float length(const sf::Vector2f& v)
    {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }
}

void handle_particle_collision(Ball& a, Ball& b)
{
    sf::Vector2f delta = b.get_position() - a.get_position();
    float dist = util::length(delta);
    float penetration = (a.get_radius() + b.get_radius()) - dist;

    if (penetration > 0.f) {
        sf::Vector2f normal = util::normalize(delta);
        sf::Vector2f relative_vel = b.get_velocity() - a.get_velocity();
        float vel_along_normal = util::dot(relative_vel, normal);

        if (vel_along_normal < 0.f) {
            float e = 1.0f; // elastic
            float j = -(1 + e) * vel_along_normal;
            j /= (1 / a.get_mass()) + (1 / b.get_mass());

            sf::Vector2f impulse = j * normal;
            a.set_velocity(a.get_velocity() - impulse / a.get_mass());
            b.set_velocity(b.get_velocity() + impulse / b.get_mass());

            sf::Vector2f correction = normal * (penetration / (a.get_mass() + b.get_mass()));
            a.set_position(a.get_position() - correction * b.get_mass());
            b.set_position(b.get_position() + correction * a.get_mass());
        }
    }
}

bool handle_box_collision(Ball& ball, const Box& box) {
    sf::Vector2f pos = ball.get_position();
    sf::Vector2f vel = ball.get_velocity();
    float r = ball.get_radius();

    sf::Vector2f box_pos = box.get_position();
    sf::Vector2f size = box.get_size();

    float left = box_pos.x;
    float right = box_pos.x + size.x;
    float top = box_pos.y;
    float bottom = box_pos.y + size.y;

    // Horizontal reflection
    if (pos.x - r < left || pos.x + r > right) {
        vel.x = -vel.x;
        pos.x = (pos.x - r < left) ? left + r : right - r;
    }

    // Top collision
    if (pos.y - r < top) {
        vel.y = -vel.y;
        pos.y = top + r;
    }

    // Bottom collision — this triggers a "fall"
    if (pos.y + r > bottom) {
        return true; // Ball fell
    }

    ball.set_velocity(vel);
    ball.set_position(pos);
    return false;
}


void handle_brick_collision(Ball& ball, Brick& brick)
{
    if (brick.was_hit())
        return;

    const sf::Vector2f ball_pos = ball.get_position();
    const float r = ball.get_radius();

    const sf::Vector2f brick_pos = brick.get_position();
    const sf::Vector2f brick_size = { brick.get_width(), brick.get_height() };
    const sf::Vector2f half = brick_size / 2.f;

    const sf::Vector2f delta = ball_pos - brick_pos;
    const sf::Vector2f abs_delta = { std::abs(delta.x), std::abs(delta.y) };

    // Check for overlap
    if (abs_delta.x > half.x + r || abs_delta.y > half.y + r)
        return; // no collision

    // Collision occurred: decide axis of resolution
    const float overlap_x = (half.x + r) - abs_delta.x;
    const float overlap_y = (half.y + r) - abs_delta.y;

    sf::Vector2f new_velocity = ball.get_velocity();
    sf::Vector2f new_position = ball_pos;

    if (overlap_x < overlap_y) {
        // Collided horizontally
        new_velocity.x *= -1.f;
        new_position.x += (delta.x < 0.f ? -overlap_x : overlap_x);
    } else {
        // Collided vertically
        new_velocity.y *= -1.f;
        new_position.y += (delta.y < 0.f ? -overlap_y : overlap_y);
    }

    ball.set_velocity(new_velocity);
    ball.set_position(new_position);
    brick.mark_hit();
}

void handle_paddle_collision(Ball& ball, const Paddle& paddle)
{
    // Get positions and sizes
    const sf::Vector2f ball_pos = ball.get_position();
    const float r = ball.get_radius();

    const sf::Vector2f paddle_pos = paddle.get_position();
    const sf::Vector2f paddle_size = paddle.get_size();
    const sf::Vector2f half = paddle_size / 2.f;

    // Calculate AABB overlap
    const float left   = paddle_pos.x - half.x;
    const float right  = paddle_pos.x + half.x;
    const float top    = paddle_pos.y - half.y;
    const float bottom = paddle_pos.y + half.y;

    // Ball's bounding box
    const float ball_left   = ball_pos.x - r;
    const float ball_right  = ball_pos.x + r;
    const float ball_top    = ball_pos.y - r;
    const float ball_bottom = ball_pos.y + r;

    // Check for intersection
    bool overlaps_x = ball_right > left && ball_left < right;
    bool overlaps_y = ball_bottom > top && ball_top < bottom;

    if (!overlaps_x || !overlaps_y)
        return;

    // Reflect ball vertically
    sf::Vector2f velocity = ball.get_velocity();
    velocity.y = -std::abs(velocity.y); // always bounce upward
    ball.set_velocity(velocity);

    // Move ball above the paddle to prevent sticking
    sf::Vector2f new_pos = ball_pos;
    new_pos.y = top - r - 0.1f;
    ball.set_position(new_pos);
}


} // namespace collision_detector

} // namespace arkanoid
