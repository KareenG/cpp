#include "arkanoid/input_name.hpp"
#include <cctype>

namespace arkanoid {

void NameEntryDialog::show(const std::string& prompt, Callback on_done) {
    input_.clear();
    prompt_ = prompt;
    callback_ = std::move(on_done);
    active_ = true;
    done_ = false;
}

void NameEntryDialog::handle_text(uint32_t unicode) {
    if (!active_ || input_.size() >= max_length)
        return;
    if (unicode >= 32 && unicode <= 126)
        input_ += static_cast<char>(unicode);
}

void NameEntryDialog::handle_key(sf::Keyboard::Key key) {
    if (!active_) return;
    if (key == sf::Keyboard::Key::Backspace && !input_.empty()) {
        input_.pop_back();
    } else if (key == sf::Keyboard::Key::Enter && !input_.empty()) {
        active_ = false;
        done_ = true;
        if (callback_) callback_(input_);
    }
}

void NameEntryDialog::update(float) {}

void NameEntryDialog::render(sf::RenderWindow& window, const UI& ui) const {
    if (!active_) return;
    ui.draw_name_input(window, prompt_, input_);
}

bool NameEntryDialog::is_active() const { return active_; }
bool NameEntryDialog::finished() const { return done_; }
void NameEntryDialog::reset() {
    active_ = false;
    done_ = false;
    input_.clear();
    prompt_.clear();
    callback_ = nullptr;
}
const std::string& NameEntryDialog::input() const { return input_; }
const std::string& NameEntryDialog::prompt() const { return prompt_; }

} // namespace arkanoid
