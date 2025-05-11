#pragma once

#include "arkanoid/box/entity.hpp"

namespace box
{

class Box : public Entity {
public:
    Box(const sf::Vector2f& position,
        const sf::Vector2f& size,
        sf::Color border_color = sf::Color::White,
        sf::Color fill_color = sf::Color::Transparent,
        float thickness = 2.f);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;

    sf::FloatRect get_bounds() const;

    sf::Vector2f get_size() const;
    sf::Vector2f get_position() const;
    sf::Vector2f get_velocity() const override;
    float get_radius() const override;

    void set_velocity(const sf::Vector2f&) override;

private:
    sf::Vector2f size_;
    float thickness_;
    sf::RectangleShape top_, bottom_, left_, right_;
    sf::RectangleShape background_;
};

} // namespace box
