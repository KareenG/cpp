#include "arkanoid/ball.hpp"

namespace arkanoid {

Ball::Ball(const sf::Vector2f& position, float radius, const sf::Vector2f& velocity, sf::Color color, float mass)
: radius_{radius}
, velocity_{velocity}
, shape_{radius_}
, mass_{mass}
{
    position_ = position;
    start_position_ = position;
    shape_.setOrigin( {radius_, radius_} );
    shape_.setPosition(position_);
    shape_.setFillColor(color);
    shape_.setOutlineColor(sf::Color::Black);
    shape_.setOutlineThickness(1.f);
}

void Ball::update(float dt)
{
    position_ += velocity_ * dt;
    shape_.setPosition(position_);
}

void Ball::draw(sf::RenderWindow& window) const
{
    window.draw(shape_);
}

sf::Vector2f Ball::get_velocity() const
{
    return velocity_;
}

void Ball::set_velocity(const sf::Vector2f& v)
{
    velocity_ = v;
}

float Ball::get_radius() const
{
    return radius_;
}

float Ball::get_mass() const
{
    return mass_;
}

void Ball::reset()
{
    velocity_ = start_velocity_;
    position_ = start_position_;
    shape_.setPosition(position_);
}


} // namespace arkanoid