#pragma once
#include "arkanoid/entity.hpp"

namespace arkanoid {

class Ball : public Entity {
public:
    Ball(const sf::Vector2f& position, float radius, const sf::Vector2f& velocity,
         sf::Color color, float mass = 1.f);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;

    sf::Vector2f get_velocity() const override;
    void set_velocity(const sf::Vector2f& v) override;

    float get_radius() const;
    float get_mass() const;

    void reset();

private:
    float radius_;
    sf::Vector2f velocity_;
    sf::CircleShape shape_;
    sf::Vector2f start_position_;
    sf::Vector2f start_velocity_;
    float mass_;
};

} // namespace arkanoid
