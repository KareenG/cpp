#include "arkanoid/box/box.hpp"

namespace box
{

Box::Box(const sf::Vector2f& position, const sf::Vector2f& size, sf::Color fill_color, sf::Color border_color, float thickness)
: size_(size)
, thickness_(thickness)
{
    is_fixed_ = true;
    position_ = position;
    color_ = border_color;

    background_.setPosition(position);
    background_.setSize(size_);
    background_.setFillColor(fill_color);
    background_.setOutlineThickness(0);

    top_.setSize({ size_.x, thickness_ });
    top_.setPosition(sf::Vector2f(position_.x, position_.y));
    top_.setFillColor(border_color);

    bottom_.setSize({ size_.x, thickness_ });
    bottom_.setPosition(sf::Vector2f(position_.x, position_.y + size_.y - thickness_));
    bottom_.setFillColor(border_color);

    left_.setSize({ thickness_, size_.y });
    left_.setPosition(sf::Vector2f(position_.x, position_.y));
    left_.setFillColor(border_color);

    right_.setSize({ thickness_, size_.y });
    right_.setPosition(sf::Vector2f(position_.x + size_.x - thickness_, position_.y));
    right_.setFillColor(border_color);

    for (auto* side : {&top_, &bottom_, &left_, &right_}) {
        side->setFillColor(border_color);
    }
}

void Box::update(float)
{
}

void Box::draw(sf::RenderWindow& window) const
{
    window.draw(background_);
    window.draw(top_);
    window.draw(bottom_);
    window.draw(left_);
    window.draw(right_);
}

sf::FloatRect Box::get_bounds() const
{
    return background_.getGlobalBounds();
}

sf::Vector2f Box::get_size() const
{
    return size_;
}

sf::Vector2f Box::get_position() const
{
    return background_.getPosition();
}

sf::Vector2f Box::get_velocity() const
{
    return sf::Vector2f{0.f, 0.f}; // static
}

float Box::get_radius() const
{
    return 0.f; // not applicable
}

void Box::set_velocity(const sf::Vector2f&)
{
    // ignored
}

} // namespace box
