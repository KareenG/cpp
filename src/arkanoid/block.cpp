#include "arkanoid/block.hpp"

namespace arkanoid {

void Block::draw(sf::RenderWindow& window) const
{
    window.draw(shape_);
}

} // namespace arkanoid
