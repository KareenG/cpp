#pragma once

#include <vector>
#include <string>

namespace arkanoid
{

struct LevelData {
    std::vector<std::string> pattern_;
    int level_num_ = 1;
    float padding_top_ = 100.f;
    float padding_left_ = 40.f;
    float padding_right_ = 40.f;
    float brick_height_ = 30.f;
};

} // namespace arkanoid
