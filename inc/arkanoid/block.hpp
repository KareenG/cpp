#pragma once

#include "arkanoid/entity.hpp"

namespace arkanoid {

class Block : public Entity {
public:
    void draw(sf::RenderWindow& window) const override;
    virtual float get_width() const;
    virtual float get_height() const;
    sf::Vector2f get_size() const;

protected:
    float width_;
    float height_;
    sf::RectangleShape shape_;
};

} // namespace arkanoid
