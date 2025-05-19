#include "arkanoid/overlay_layer.hpp"
#include "arkanoid/ui.hpp"

namespace arkanoid {

OverlayLayer::OverlayLayer()
: type_(OverlayType::None)
, timer_(0.f)
, done_(false)
{
}

void OverlayLayer::show(OverlayType type) {
    type_ = type;
    timer_ = 0.f;
    done_ = false;
}

void OverlayLayer::update(float dt)
{
    if (type_ == OverlayType::None || done_) {
        return;
    }

    if (is_confirmation()) {
        // Confirmation overlays are finished via user input (confirm/cancel)
        return;
    }

    timer_ += dt;
    if (timer_ >= overlay_duration(type_)) {
        done_ = true;
    }
}

void OverlayLayer::render(sf::RenderWindow& window, const UI& ui) const
{
    if (type_ == OverlayType::None) {
        return;
    }
    ui.draw_overlay(window, type_);
}

bool OverlayLayer::is_active() const
{
    return type_ != OverlayType::None && !done_;
}

bool OverlayLayer::is_confirmation() const
{
    return type_ == OverlayType::QuitConfirm;
}

void OverlayLayer::confirm()
{
    if (is_confirmation())
        done_ = true;
}

void OverlayLayer::cancel()
{
    if (is_confirmation())
        done_ = true;
}

bool OverlayLayer::finished() const
{
    return done_;
}

OverlayType OverlayLayer::type() const
{
    return type_;
}

float OverlayLayer::overlay_duration(OverlayType type) const
{
    switch (type) {
    case OverlayType::Win:
        return consts:: OverlayDuration;//3.f; // 10.f
    case OverlayType::GameOver:
        return consts:: OverlayDuration;//2.f; // 20.f
    default:
        return 0.f; // Confirmation and None have no timer duration
    }
}

} // namespace arkanoid
