#pragma once

#include "arkanoid/box/particle.hpp"
#include "arkanoid/box/box.hpp"

namespace box::collision_detector
{

void handle_particle_collision(Particle& a, Particle& b);
void handle_box_collision(Particle& particle, const Box& box);

namespace util {
    sf::Vector2f normalize(const sf::Vector2f& v);
    float dot(const sf::Vector2f& a, const sf::Vector2f& b);
    float length(const sf::Vector2f& v);
}

} // namespace box::collision_detector
