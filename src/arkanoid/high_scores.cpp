#include "arkanoid/high_scores.hpp"
#include "arkanoid/resources_and_consts.hpp"
#include <algorithm>
#include <iomanip>
#include <sstream>

namespace arkanoid {

std::string HighScoreEntry::display() const
{
    std::ostringstream oss;
    oss << std::setw(consts::MaxNameLength) << std::left << name
        << "  " << std::setw(6) << score
        << "  " << std::fixed << std::setprecision(2) << time_seconds << "s";
    return oss.str();
}

bool high_score_comparator(const HighScoreEntry& a, const HighScoreEntry& b)
{
    if (a.score != b.score) {
        return a.score > b.score;
    }
    return a.time_seconds < b.time_seconds;
}

bool HighScoreTable::add_score(const std::string& name, int score, float time_seconds)
{
    std::string n = name.substr(0, consts::MaxNameLength);
    top_k_.push_back({n, score, time_seconds});
    std::sort(top_k_.begin(), top_k_.end(), high_score_comparator);
    if (top_k_.size() > consts::MaxScores) {
        top_k_.resize(consts::MaxScores);
    }
    for (const auto& entry : top_k_) {
        if (entry.name == n && entry.score == score && entry.time_seconds == time_seconds) {
            return true;
        }
    }
    return false;
}

bool HighScoreTable::qualifies(int score, float time_seconds) const
{
    if (top_k_.size() < consts::MaxScores) {
        return true;
    }
    const auto& worst = top_k_.back();
    if (score > worst.score) {
        return true;
    }
    if (score == worst.score && time_seconds < worst.time_seconds) {
        return true;
    }
    return false;
}

const std::vector<HighScoreEntry>& HighScoreTable::entries() const
{
    return top_k_;
}

void HighScoreTable::clear()
{
    top_k_.clear();
}

std::string HighScoreTable::display() const
{
    std::ostringstream oss;

    // Define column widths
    constexpr int col_rank  = 10;
    constexpr int col_name  = 16;
    constexpr int col_score = 14;
    constexpr int col_time  = 12;

    // Print header
    oss << std::left
        << std::setw(col_rank)  << "Rank"
        << std::setw(col_name)  << "Name"
        << std::setw(col_score) << "Score"
        << std::setw(col_time)  << "Time"
        << '\n';

    oss << std::string(col_rank + col_name + col_score + col_time, '-') << '\n';

    int rank = 1;
    for (const auto& entry : top_k_) {
        oss << std::left << std::setw(col_rank)  << rank
            << std::setw(col_name)  << entry.name
            << std::setw(col_score) << entry.score
            << std::setw(col_time - 1) << std::fixed << std::setprecision(2) << entry.time_seconds << "s"
            << '\n';
        if (++rank > consts::MaxScores) {
            break;
        }
    }

    if (top_k_.empty()) {
        oss << "No high scores yet.\n";
    }

    return oss.str();
}

} // namespace arkanoid
