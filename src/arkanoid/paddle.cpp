#include "arkanoid/paddle.hpp"
#include "arkanoid/input_controller.hpp"

namespace arkanoid {

Paddle::Paddle(const sf::Vector2f& size, const sf::Vector2f& position, sf::Color color, float speed)
: speed_{speed}
, velocity_{0.f, 0.f}
{
    width_ = size.x;
    height_ = size.y;
    position_ = position;
    start_position_ = position;
    color_ = color;
    is_fixed_ = false;

    shape_.setSize(size);
    shape_.setOrigin( {size.x / 2.f, size.y / 2.f} );
    shape_.setPosition(position);
    shape_.setFillColor(color);
    shape_.setOutlineColor(sf::Color::Black);
    shape_.setOutlineThickness(1.f);

    input_controller::bind_key(sf::Keyboard::Key::Space, [this]() {
        is_fixed_ = !is_fixed_;
    });

    // // Add input bindings for left and right movement
    // input_controller::bind_key(sf::Keyboard::Key::Left, [this]() {
    //     if (!is_fixed_) {
    //         move_left();
    //     }
    // });
    
    // input_controller::bind_key(sf::Keyboard::Key::Right, [this]() {
    //     if (!is_fixed_) {
    //         move_right();
    //     }
    // });
}

void Paddle::move_left()
{
    velocity_.x = -speed_;
}

void Paddle::move_right()
{
    velocity_.x = speed_;
}

bool Paddle::is_fixed() const
{
    return false;  // Paddle is controlled and moves
}

void Paddle::set_fixed(bool fixed)
{
    is_fixed_ = fixed;
}

void Paddle::resize(float width, float height)
{
    width_ = width;
    height_ = height;

    shape_.setSize({width_, height_});
    shape_.setOrigin( {width_ / 2.f, height_ / 2.f} );
}

void Paddle::draw(sf::RenderWindow& window) const
{
    window.draw(shape_);
}

void Paddle::update(float dt)
{
    position_ += velocity_ * dt;
    shape_.setPosition(position_);
    velocity_ = {0.f, 0.f};  // reset movement after each frame
}

sf::Vector2f Paddle::get_velocity() const
{
    return velocity_;
}

void Paddle::set_velocity(const sf::Vector2f& v)
{
    velocity_ = v;
}

void Paddle::reset()
{
    velocity_ = {0.f, 0.f};
    position_ = start_position_;
    shape_.setPosition(position_);
    is_fixed_ = false;
}


} // namespace arkanoid
