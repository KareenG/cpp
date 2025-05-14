#include <SFML/Graphics.hpp>
#include <cassert>

#include "arkanoid/brick.hpp"

namespace arkanoid {

Brick::Brick(const sf::Vector2f& size, const sf::Vector2f& position, sf::Color color)
: was_hit_{false}
{
    width_ = size.x;
    height_ = size.y;
    position_ = position;
    color_ = color;

    shape_.setSize(size);
    shape_.setOrigin(size / 2.f);  // same as {size.x/2, size.y/2}
    shape_.setPosition(position);
    shape_.setFillColor(color);
    shape_.setOutlineColor(sf::Color::Black);
    shape_.setOutlineThickness(1.f);
}

void Brick::draw(sf::RenderWindow& window) const
{
    if (!was_hit_) {
        window.draw(shape_);
    }
}

bool Brick::was_hit() const
{
    return was_hit_;
}

void Brick::mark_hit()
{
    was_hit_ = true;
    shape_.setFillColor(sf::Color::Transparent);
}

sf::Vector2f Brick::get_velocity() const
{
    return {0.f, 0.f};
}

bool Brick::is_fixed() const
{
    return true;
}

void Brick::update(float)//dt
{
}

void Brick::set_position(const sf::Vector2f&)
{
    assert(false && "Brick::set_position() is disabled: bricks are fixed.");
}

void Brick::set_color(const sf::Color&)
{
    assert(false && "Brick::set_color() is disabled: bricks are immutable.");
}

void Brick::set_velocity(const sf::Vector2f&)
{
    assert(false && "Brick::set_velocity() is disabled: bricks do not move.");
}

void Brick::set_fixed(bool)
{
    assert(false && "Brick::set_fixed() is disabled: bricks are always fixed.");
}

} // namespace arkanoid
