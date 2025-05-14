#pragma once

#include <string>

namespace arkanoid {

class Player {
public:
    explicit Player(const std::string& name, std::size_t initial_lives = 3);

    std::size_t get_lives() const;
    void increase_life();
    void decrease_life();
    void add_score(std::size_t amount);
    std::size_t get_score() const;
    void reset();

private:
    std::string name_;
    std::size_t lives_left_;
    std::size_t score_;
};

} // namespace arkanoid
