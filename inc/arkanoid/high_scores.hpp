#pragma once

#include <vector>
#include <string>

#include "arkanoid/ui.hpp"
#include "arkanoid/high_score_entry.hpp"
#include "arkanoid/i_high_score_storage.hpp" 

namespace arkanoid {

// Comparator for sorting entries (higher score, then shorter time)
bool high_score_comparator(const HighScoreEntry& a, const HighScoreEntry& b);

class IHighScoreStorage;

class HighScoreTable {
public:
    //HighScoreTable() = default;
    explicit HighScoreTable(std::unique_ptr<IHighScoreStorage> storage);

    ~HighScoreTable() noexcept = default;
    HighScoreTable(HighScoreTable const& other) = delete;
    HighScoreTable& operator=(HighScoreTable const& other) = delete;

    // Try to add a score, returns true if inserted
    bool add_score(const std::string& name, ScoreType score, float time_s);

    // Returns true if score/time would be in top 10
    //bool qualifies(int score, float time_ms) const;
    bool qualifies(ScoreType score, float time_s) const;

    // Access the current entries
    const std::vector<HighScoreEntry>& entries() const;

    // Clear all scores
    void clear();

    std::string display() const;

    void render(sf::RenderWindow& window, const UI& ui, unsigned font_size = consts::TableTextSize, float start_y = consts::OffsetYTopScoresTable) const;

private:
    std::vector<HighScoreEntry> top_k_;
    std::unique_ptr<IHighScoreStorage> storage_;
};

} // namespace arkanoid
