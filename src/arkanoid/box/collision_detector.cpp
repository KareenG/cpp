#include <cmath>

#include "arkanoid/box/collision_detector.hpp"

namespace box::collision_detector::util
{

float dot(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return a.x * b.x + a.y * b.y;
}

float length_sq(const sf::Vector2f& v)
{
    return v.x * v.x + v.y * v.y;
}

float length(const sf::Vector2f& v)
{
    return std::sqrt(length_sq(v));
}

sf::Vector2f normalize(const sf::Vector2f& v)
{
    float len = length(v);
    return len > 0 ? v / len : sf::Vector2f{0.f, 0.f};
}

} // namespace box::collision_detector::util

namespace box::collision_detector
{

sf::Vector2f reflect(const sf::Vector2f& v, const sf::Vector2f& normal)
{
    return v - 2.f * util::dot(v, normal) * normal;
}

void bounce_off_walls(Entity& ball, const Box& box)
{
    const sf::Vector2f& position = box.get_position();
    const sf::Vector2f& size = box.get_size();

    float left   = position.x;
    float right  = position.x + size.x;
    float top    = position.y;
    float bottom = position.y + size.y;

    auto pos = ball.get_position();
    auto vel = ball.get_velocity();
    float r = ball.get_radius();

    bool bounced = false;

    if (pos.x - r < left) {
        pos.x = left + r;
        vel = reflect(vel, {1.f, 0.f});
        bounced = true;
    } else if (pos.x + r > right) {
        pos.x = right - r;
        vel = reflect(vel, {-1.f, 0.f});
        bounced = true;
    }

    if (pos.y - r < top) {
        pos.y = top + r;
        vel = reflect(vel, {0.f, 1.f});
        bounced = true;
    } else if (pos.y + r > bottom) {
        pos.y = bottom - r;
        vel = reflect(vel, {0.f, -1.f});
        bounced = true;
    }

    if (bounced) {
        ball.set_position(pos);
        ball.set_velocity(vel);
    }
}

void bounce_particles(Entity& a, Entity& b)
{
    auto x1 = a.get_position();
    auto x2 = b.get_position();
    auto v1 = a.get_velocity();
    auto v2 = b.get_velocity();
    float r1 = a.get_radius();
    float r2 = b.get_radius();

    sf::Vector2f delta = x2 - x1;
    float dist_sq = util::dot(delta, delta);
    float radius_sum = r1 + r2;

    if (dist_sq == 0.f || dist_sq > radius_sum * radius_sum)
        return;

    float m1 = r1 * r1; // mass ∝ area ∝ radius^2
    float m2 = r2 * r2;

    sf::Vector2f normal = util::normalize(delta);
    sf::Vector2f rel_vel = v1 - v2;
    float impact_speed = util::dot(rel_vel, normal);
    if (impact_speed > 0) return;

    float impulse_mag = (2 * impact_speed) / (m1 + m2);
    sf::Vector2f impulse = impulse_mag * normal;

    a.set_velocity(v1 - impulse * m2);
    b.set_velocity(v2 + impulse * m1);

    // Position correction to avoid overlap
    float dist = std::sqrt(dist_sq);
    float overlap = 0.5f * (radius_sum - dist);
    sf::Vector2f correction = normal * overlap;
    a.set_position(x1 - correction);
    b.set_position(x2 + correction);
}

} // namespace box::collision_detector