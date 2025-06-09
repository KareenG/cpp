#include "arkanoid/standard_brick.hpp"

namespace arkanoid
{

StandardBrick::StandardBrick(const sf::Vector2f& size, const sf::Vector2f& position, sf::Color color, int score)
: Brick(size, position, color)
, score_(score)
{
}

void StandardBrick::on_hit()
{
    destroyed_ = true;
    shape_.setFillColor(sf::Color::Transparent);
    shape_.setOutlineColor(sf::Color::Transparent);
}

int StandardBrick::score(int) const
{ 
    return score_; 
}
bool StandardBrick::is_destroyed() const 
{
    return destroyed_;
}
bool StandardBrick::is_indestructible() const
{
    return false;
}

void StandardBrick::update(float) { /* no-op for bricks */ }
sf::Vector2f StandardBrick::get_velocity() const { return {0.f, 0.f}; }
void StandardBrick::set_velocity(const sf::Vector2f&) { /* no-op */ }

} // namespace arkanoid


