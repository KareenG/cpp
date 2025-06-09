#pragma once

#include "arkanoid/brick.hpp"

namespace arkanoid {

class StandardBrick : public Brick {
public:
    StandardBrick(const sf::Vector2f& size, const sf::Vector2f& position, sf::Color color, int score);

    void on_hit() override;
    int score(int level) const override;
    bool is_destroyed() const override;
    bool is_indestructible() const override;

    void update(float dt) override;
    sf::Vector2f get_velocity() const override;
    void set_velocity(const sf::Vector2f&) override;


private:
    int score_;
    bool destroyed_ = false;
};

} // namespace arkanoid
