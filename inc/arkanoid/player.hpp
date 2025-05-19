#pragma once

#include <string>

namespace arkanoid {

class Player {
public:
    Player() = default;
    explicit Player(const std::string& name, std::size_t initial_lives = 3);

    std::size_t get_lives() const;
    void increase_life();
    void decrease_life();
    void add_score(std::size_t amount);
    std::size_t get_score() const;
    void reset();
    void update_max_score();
    size_t max_score() const;

private:
    std::string name_;
    std::size_t lives_left_ = 3;
    std::size_t score_ = 0;
    std::size_t max_score_ = 0;
};

} // namespace arkanoid
