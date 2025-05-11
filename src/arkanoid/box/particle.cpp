#include "arkanoid/box/particle.hpp"

namespace box
{

Particle::Particle(const sf::Vector2f& position, float radius, const sf::Vector2f& velocity, sf::Color color)
: radius_(radius)
, velocity_(velocity)
{
    position_ = position;
    color_ = color;
    shape_.setRadius(radius);
    shape_.setOrigin( {radius, radius} );
    shape_.setPosition(position);
    shape_.setFillColor(color);
    shape_.setOutlineThickness(2.f);
    shape_.setOutlineColor(sf::Color::Black);
}

void Particle::update(float dt)
{
    if (!is_fixed_) {
        position_ += velocity_ * dt;
        shape_.setPosition(position_);
    }
}

void Particle::draw(sf::RenderWindow& window) const
{
    window.draw(shape_);
}

sf::Vector2f Particle::get_velocity() const
{
    return velocity_;
}
void Particle::set_velocity(const sf::Vector2f& v)
{
    velocity_ = v;
}
float Particle::get_radius() const
{
    return radius_;
}

} // namespace box
