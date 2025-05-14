#include "arkanoid/block.hpp"

namespace arkanoid {

void Block::draw(sf::RenderWindow& window) const
{
    window.draw(shape_);
}

float Block::get_width() const
{
    return width_;
}

float Block::get_height() const
{
    return height_;
}

sf::Vector2f Block::get_size() const
{
    return {width_, height_};
}

} // namespace arkanoid
