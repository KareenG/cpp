#pragma once

#include <SFML/Graphics.hpp>

#include "arkanoid/box/entity.hpp"
#include "arkanoid/box/box.hpp"

namespace box::collision_detector
{
    
sf::Vector2f reflect(const sf::Vector2f& v, const sf::Vector2f& normal);
void bounce_off_walls(Entity& ball, const Box& box);
void bounce_particles(Entity& a, Entity& b);
    
} // namespace box::collision_detector

namespace box::collision_detector::util
{

float dot(const sf::Vector2f& a, const sf::Vector2f& b);
float length_sq(const sf::Vector2f& v);
float length(const sf::Vector2f& v);
sf::Vector2f normalize(const sf::Vector2f& v);
    
} // namespace box::collision_detector::util