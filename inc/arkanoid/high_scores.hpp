#pragma once

#include <vector>
#include <string>

#include "arkanoid/ui.hpp"

namespace arkanoid {

struct HighScoreEntry {
    std::string name;
    int score;
    float time_seconds;
    std::string display() const;
};

// Comparator for sorting entries (higher score, then shorter time)
bool high_score_comparator(const HighScoreEntry& a, const HighScoreEntry& b);

class HighScoreTable {
public:
    HighScoreTable() = default;
    ~HighScoreTable() noexcept = default;
    HighScoreTable(HighScoreTable const& other) = delete;
    HighScoreTable& operator=(HighScoreTable const& other) = delete;

    // Try to add a score, returns true if inserted
    bool add_score(const std::string& name, int score, float time_seconds);

    // Returns true if score/time would be in top 10
    bool qualifies(int score, float time_seconds) const;

    // Access the current entries
    const std::vector<HighScoreEntry>& entries() const;

    // Clear all scores (optional utility)
    void clear();

    std::string display() const;

    void render(sf::RenderWindow& window, const UI& ui, unsigned font_size = consts::TableTextSize, float start_y = consts::OffsetYTopScoresTable) const;

private:
    std::vector<HighScoreEntry> top_k_;
};

} // namespace arkanoid
