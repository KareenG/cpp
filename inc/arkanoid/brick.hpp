#pragma once
#include <cassert>
#include "arkanoid/block.hpp"

namespace arkanoid {

class Brick : public Block {
public:
    Brick(const sf::Vector2f& size, const sf::Vector2f& position, sf::Color color);

    void draw(sf::RenderWindow& window) const override;

    bool was_hit() const;
    void mark_hit();

    sf::Vector2f get_velocity() const override;
    bool is_fixed() const override;

private:
    // Disable all setters
    void set_position(const sf::Vector2f&) override;
    void set_color(const sf::Color&) override;
    void set_velocity(const sf::Vector2f&) override;
    void set_fixed(bool) override;

    void update(float dt) override;

private:
   bool was_hit_ = false;
//sf::RectangleShape shape_;
};

} // namespace arkanoid
