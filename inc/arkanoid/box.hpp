#pragma once

#include "arkanoid/entity.hpp"

namespace arkanoid
{

class Box : public Entity {
public:
    Box(const sf::Vector2f& position,
        const sf::Vector2f& size,
        sf::Color border_color = sf::Color::White,
        sf::Color fill_color = sf::Color::Transparent,
        float thickness = 2.f);

    void draw(sf::RenderWindow& window) const override;

    sf::Vector2f get_size() const;
    sf::Vector2f get_position() const;
    sf::Vector2f get_velocity() const override;

    float left() const;
    float right() const;
    float top() const;
    float bottom() const;

private:
    void set_position(const sf::Vector2f&) override;
    void set_color(const sf::Color&) override;
    void set_velocity(const sf::Vector2f&) override;
    void set_fixed(bool) override;

    void update(float dt) override;

private:
    sf::Vector2f size_;
    float thickness_;
    sf::RectangleShape top_, bottom_, left_, right_;
    sf::RectangleShape background_;
};

} // namespace arkanoid
