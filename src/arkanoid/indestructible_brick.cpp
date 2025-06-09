#include "arkanoid/indestructible_brick.hpp"

namespace arkanoid
{

IndestructibleBrick::IndestructibleBrick(const sf::Vector2f& size, const sf::Vector2f& position, sf::Color color)
: Brick(size, position, color)
{
}

void IndestructibleBrick::on_hit() {
    // do nothing
    // destroyed_ = true;
    // shape_.setFillColor(sf::Color::Transparent);
}

int IndestructibleBrick::score(int) const 
{
    return 0;
}

bool IndestructibleBrick::is_destroyed() const 
{
    return false;
}

bool IndestructibleBrick::is_indestructible() const 
{
    return true;
}

void IndestructibleBrick::update(float) { /* no-op for bricks */ }
sf::Vector2f IndestructibleBrick::get_velocity() const { return {0.f, 0.f}; }
void IndestructibleBrick::set_velocity(const sf::Vector2f&) { /* no-op */ }

} // namespace arkanoid
