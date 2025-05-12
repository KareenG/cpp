#pragma once

#include "arkanoid/entity.hpp"

namespace arkanoid {

class Block : public Entity {
public:
    void draw(sf::RenderWindow& window) const override;

protected:
    float width_;
    float height_;
    sf::RectangleShape shape_;
};

} // namespace arkanoid
