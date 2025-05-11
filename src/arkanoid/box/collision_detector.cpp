#include <cmath>

#include "arkanoid/box/collision_detector.hpp"

namespace box::collision_detector {

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

void handle_particle_collision(Particle& a, Particle& b)
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

void handle_box_collision(Particle& particle, const Box& box)
{
    sf::Vector2f pos = particle.get_position();
    sf::Vector2f vel = particle.get_velocity();
    float r = particle.get_radius();

    sf::Vector2f box_pos = box.get_position();
    sf::Vector2f size = box.get_size();

    float left = box_pos.x;
    float right = box_pos.x + size.x;
    float top = box_pos.y;
    float bottom = box_pos.y + size.y;

    if (pos.x - r < left || pos.x + r > right) {
        vel.x = -vel.x;
        pos.x = (pos.x - r < left) ? left + r : right - r;
    }

    if (pos.y - r < top || pos.y + r > bottom) {
        vel.y = -vel.y;
        pos.y = (pos.y - r < top) ? top + r : bottom - r;
    }

    particle.set_velocity(vel);
    particle.set_position(pos);
}

} // namespace box::collision_detector
