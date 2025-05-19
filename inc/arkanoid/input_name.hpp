#pragma once

#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

#include "arkanoid/i_input_dialog.hpp"
#include "arkanoid/i_io_overly.hpp"

namespace arkanoid {

class NameEntryDialog : public IOverlay, public IInputDialog {
public:
    using Callback = std::function<void(const std::string&)>;
    NameEntryDialog() = default;

    // IInputDialog
    void show(const std::string& prompt, Callback on_done) override;
    void handle_text(uint32_t unicode) override;
    void handle_key(sf::Keyboard::Key key) override;
    void reset() override;
    const std::string& input() const override;
    const std::string& prompt() const override;

    // IOverlay
    void update(float dt) override;
    void render(sf::RenderWindow& window, const UI& ui) const override;
    bool is_active() const override;
    bool finished() const override;

private:
    std::string input_;
    std::string prompt_;
    Callback callback_;
    bool active_ = false;
    bool done_ = false;
    std::size_t max_length = consts::MaxNameLength;
};


} // namespace arkanoid
