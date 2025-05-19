#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "arkanoid/resources_and_consts.hpp"
#include "arkanoid/i_io_overly.hpp"

namespace arkanoid {

class OverlayLayer : public IOverlay { // Implement the interface!
public:
    using NameInputCallback = std::function<void(const std::string&)>;

    OverlayLayer();

    // Show a new overlay of the given type (resets timer, etc)
    void show(OverlayType type);

    // IOverlay implementations:
    void update(float dt) override;
    void render(sf::RenderWindow& window, const class UI& ui) const override;
    bool is_active() const override;
    bool finished() const override;

    // OverlayLayer-specific:
    bool is_confirmation() const;
    void confirm();
    void cancel();
    OverlayType type() const;

private:
    OverlayType type_ = OverlayType::None;
    float timer_ = 0.f;
    bool done_ = false;
    float overlay_duration(OverlayType type) const;
};

} // namespace arkanoid
