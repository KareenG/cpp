#include "arkanoid/box/particle.hpp"

namespace box {

Particle::Particle(const sf::Vector2f& position, float radius, const sf::Vector2f& velocity, sf::Color color, float mass)
    : radius_(radius), mass_(mass), velocity_(velocity) {
    position_ = position;
    shape_.setRadius(radius_);
    shape_.setOrigin({radius_, radius_});
    shape_.setPosition(position_);
    shape_.setFillColor(color);
    shape_.setOutlineColor(sf::Color::Black);
    shape_.setOutlineThickness(1.f);
}

void Particle::update(float dt) {
    position_ += velocity_ * dt;
    shape_.setPosition(position_);
}

void Particle::draw(sf::RenderWindow& window) const {
    window.draw(shape_);
}

sf::Vector2f Particle::get_velocity() const {
    return velocity_;
}

void Particle::set_velocity(const sf::Vector2f& v) {
    velocity_ = v;
}

float Particle::get_radius() const {
    return radius_;
}

float Particle::get_mass() const {
    return mass_;
}

} // namespace box
