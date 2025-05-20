#pragma once

#include "arkanoid/resources_and_consts.hpp"

namespace arkanoid
{
    
struct HighScoreEntry {
    std::string name;
    ScoreType score;
    float time_s;

    std::string display() const;
};

} // namespace arkanoid



