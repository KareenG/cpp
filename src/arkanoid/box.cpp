#include "arkanoid/box.hpp"
#include "arkanoid/resources_and_consts.hpp"

namespace arkanoid
{

Box::Box(const sf::Vector2f& position, const sf::Vector2u& size, sf::Color fill_color, sf::Color border_color, float thickness)
: size_(size)
, thickness_(thickness)
{
    is_fixed_ = true;
    position_ = position;
    color_ = border_color;

    background_.setPosition(position);
    background_.setSize(size_);
    //background_.setFillColor(fill_color);
    (void)fill_color;
    background_.setTexture(&resources::get_texture(consts::TextureGame));
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

float Box::left() const {
    //return left_.getPosition().x;
    return left_.getPosition().x + left_.getSize().x;
}

float Box::right() const {
    return right_.getPosition().x + right_.getSize().x;
}

float Box::top() const {
    return top_.getPosition().y;
}

float Box::bottom() const {
    return bottom_.getPosition().y + bottom_.getSize().y;
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

void Box::set_position(const sf::Vector2f&)
{
}

void Box::set_color(const sf::Color&)
{
}

void Box::set_velocity(const sf::Vector2f&)
{
}

void Box::set_fixed(bool)
{
}

} // namespace arkanoid
