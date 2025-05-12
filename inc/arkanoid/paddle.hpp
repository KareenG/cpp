#pragma once

#include "arkanoid/block.hpp"

namespace arkanoid {

class Paddle : public Block {
public:

    Paddle(const sf::Vector2f& size, const sf::Vector2f& position, sf::Color color, float speed);

    void move_left();
    void move_right();

    bool is_fixed() const override;
    void set_fixed(bool fixed) override;

    void resize(float width, float height);

    void draw(sf::RenderWindow& window) const override;
    void update(float dt) override;

    sf::Vector2f get_velocity() const override;
    void set_velocity(const sf::Vector2f& v) override;

    void reset();

private:
    float speed_;
    sf::Vector2f velocity_;
    sf::Vector2f start_position_;
};

} // namespace arkanoid
