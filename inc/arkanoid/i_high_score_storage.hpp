#pragma once

#include <vector>
#include <string>

#include "arkanoid/high_score_entry.hpp"

namespace arkanoid
{
    
class IHighScoreStorage {
public:
    virtual ~IHighScoreStorage() = default;
    virtual std::vector<HighScoreEntry> load() const = 0;
    virtual void save(const std::vector<HighScoreEntry>& entries) const = 0;
    virtual void append_entry(const HighScoreEntry& entry) = 0;
};

} // namespace arkanoid



