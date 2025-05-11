#pragma once

#include "arkanoid/box/entity.hpp"

namespace box
{

class Particle : public Entity {
public:
    Particle(const sf::Vector2f& position, float radius, const sf::Vector2f& velocity, sf::Color color);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;

    sf::Vector2f get_velocity() const override;
    void set_velocity(const sf::Vector2f& v) override;

    float get_radius() const override;

private:
    float radius_;
    sf::Vector2f velocity_;
    sf::CircleShape shape_;
};

} // namespace box