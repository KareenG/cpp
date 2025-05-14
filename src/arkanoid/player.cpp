#include "arkanoid/player.hpp"

namespace arkanoid {

Player::Player(const std::string& name, std::size_t initial_lives)
: name_{name}
, lives_left_{initial_lives}
, score_{0}
{
}

std::size_t Player::get_lives() const
{
    return lives_left_;
}

void Player::increase_life()
{
    ++lives_left_;
}

void Player::decrease_life()
{
    if (lives_left_ > 0)
        --lives_left_;
}

void Player::add_score(std::size_t amount)
{
    score_ += amount;
}

std::size_t Player::get_score() const
{
    return score_;
}
void Player::Player::reset()
{
    score_ = 0;
    lives_left_ = 3;
}

} // namespace arkanoid
