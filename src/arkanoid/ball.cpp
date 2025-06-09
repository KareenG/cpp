#include <cmath>

#include "arkanoid/ball.hpp"
#include "arkanoid/input_controller.hpp"
#include "arkanoid/resources_and_consts.hpp"

namespace arkanoid {

using velocity_generator = std::function<sf::Vector2f()>;

// Generates a random initial velocity direction after collision with minor randomness on the angle.
const velocity_generator velocity_gen_ = []() {
    float angle_deg = 60.f + static_cast<float>(std::rand() % 61);  // Random angle between 60° and 120°
    float angle_rad = angle_deg * M_PI / 180.f;
    float speed = 430.f;

    // Add minor randomness to the angle after collision
    float randomness = static_cast<float>(std::rand() % 21 - 10); // Randomness between -10 and 10 degrees
    angle_deg += randomness;
    angle_rad = angle_deg * M_PI / 180.f;  // Recalculate angle in radians

    return sf::Vector2f{std::cos(angle_rad) * speed, -std::sin(angle_rad) * speed};
};

Ball::Ball(const sf::Vector2f& position, float radius, const sf::Vector2f& velocity, sf::Color color, float mass)
: radius_{radius}
, velocity_{velocity}
, shape_{radius_}
, mass_{mass}
{
    (void)color;
    position_ = position;
    start_position_ = position;
    start_velocity_ = velocity;
    shape_.setOrigin( {radius_, radius_} );
    shape_.setPosition(position_);
    //shape_.setFillColor(color);
    shape_.setTexture(&resources::get_texture(consts::TextureBall));
    // shape_.setOutlineColor(sf::Color::White);//White Black
    // shape_.setOutlineThickness(1.f);
}

void Ball::update(float dt)
{
    position_ += velocity_ * dt;
    shape_.setPosition(position_);
}

void Ball::launch() {
    //position_ = start_position_;
    if (!is_launched_) {
        is_launched_ = true;
        velocity_ = velocity_gen_(); // Ensure it's set before launch
    }
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
    is_launched_ = false;
}

} // namespace arkanoid