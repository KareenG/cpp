#include <algorithm>
#include <iomanip>
#include <sstream>

#include "arkanoid/high_scores.hpp"
#include "arkanoid/resources_and_consts.hpp"
#include "arkanoid/binary_file_high_score_storage.hpp"

namespace arkanoid {

HighScoreTable::HighScoreTable(std::unique_ptr<IHighScoreStorage> storage)
: storage_(std::move(storage))
{
    // if (storage_) {
    //     top_k_ = storage_->load();
    //     std::sort(top_k_.begin(), top_k_.end(), high_score_comparator);
    // }
    if (storage_) {
    top_k_ = storage_->load();
    std::sort(top_k_.begin(), top_k_.end(), high_score_comparator);
    if (top_k_.size() > consts::MaxScores) {
        top_k_.resize(consts::MaxScores);  // Keep only the top 10
    }
}

}

std::string HighScoreEntry::display() const
{
    std::ostringstream oss;
    oss << std::setw(consts::MaxNameLength) << std::left << name
        << "  " << std::setw(6) << score
        << "  " << std::fixed << std::setprecision(2)
        << std::fixed << std::setprecision(2) << time_s << "s";
    return oss.str();
}

bool high_score_comparator(const HighScoreEntry& a, const HighScoreEntry& b)
{
    if (a.score != b.score) {
        return a.score > b.score;
    }
    return a.time_s < b.time_s;
}

bool HighScoreTable::add_score(const std::string& name, ScoreType score, float time_s) {
    std::string n = name.substr(0, consts::MaxNameLength);
    top_k_.push_back({n, score, time_s});
    std::sort(top_k_.begin(), top_k_.end(), high_score_comparator);
    if (top_k_.size() > consts::MaxScores) {
        top_k_.resize(consts::MaxScores);
    }

    if (storage_) {
        storage_->append_entry({n, score, time_s});
    }

    return std::any_of(top_k_.begin(), top_k_.end(), [&](const auto& e) {
        return e.name == n && e.score == score && e.time_s == time_s;
    });
}


//bool HighScoreTable::qualifies(int score, float time_seconds) const
bool HighScoreTable::qualifies(ScoreType score, float time_s) const
{
    if (top_k_.size() < consts::MaxScores) {
        return true;
    }
    const auto& worst = top_k_.back();
    if (score > worst.score) {
        return true;
    }
    if (score == worst.score && time_s < worst.time_s) {
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

    if (top_k_.empty()) {
        oss << "No high scores yet.\n";
        return oss.str();
    }

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
            << std::setw(col_score) << entry.score;

        std::ostringstream time_stream;
        time_stream << std::fixed << std::setprecision(2) << entry.time_s << "s";

        oss << std::setw(col_time) << time_stream.str() << '\n';

        if (++rank > consts::MaxScores) {
            break;
        }
    }

    return oss.str();
}

void HighScoreTable::render(sf::RenderWindow& window, const UI& ui, unsigned font_size, float start_y) const
{
    // Column relative offsets (from table left)
    float name_offset  = 120.f;
    float score_offset = 380.f;
    float time_offset  = 500.f;

    // Total width for centering (add extra at end for "Time" col and padding)
    float table_width = time_offset + 130.f;

    // Center horizontally
    float center_x = (window.getSize().x - table_width) / 2.f;

    // Column absolute positions
    float col_rank_x  = center_x;
    float col_name_x  = center_x + name_offset;
    float col_score_x = center_x + score_offset;
    float col_time_x  = center_x + time_offset;
    float y_step = font_size + 8.f;

    // Center background rectangle
    float bg_x = center_x - 32.f;
    float bg_y = start_y - 50.f;
    float bg_width = table_width + 64.f;
    float bg_height = 420.f + 50.f;
    sf::RectangleShape bg({bg_width, bg_height});
    bg.setPosition( {bg_x, bg_y} );
    bg.setFillColor(sf::Color(30, 30, 30, 200));
    window.draw(bg);

    if (top_k_.empty()) {
        ui.draw_centered_text(window, consts::NoHighScoresYetText, sf::Color::White, font_size, start_y);
        return;
    }

    // Header
    ui.draw_simple_text(window, "Rank",  col_rank_x,  start_y, font_size, sf::Color::White);
    ui.draw_simple_text(window, "Name",  col_name_x,  start_y, font_size, sf::Color::White);
    ui.draw_simple_text(window, "Score", col_score_x, start_y, font_size, sf::Color::White);
    ui.draw_simple_text(window, "Time",  col_time_x,  start_y, font_size, sf::Color::White);

    // Underline
    sf::RectangleShape line;
    line.setPosition( {col_rank_x, start_y + font_size + 2.f} );
    line.setSize({col_time_x + 90.f - col_rank_x, 2.f});
    line.setFillColor(sf::Color::White);
    window.draw(line);

    float y = start_y + y_step + 6.f;
    int rank = 1;
    for (const auto& entry : top_k_) {
        ui.draw_simple_text(window, std::to_string(rank), col_rank_x, y, font_size, consts::TableTextColor);
        ui.draw_simple_text(window, entry.name, col_name_x, y, font_size, consts::TableTextColor);
        ui.draw_simple_text(window, std::to_string(entry.score), col_score_x, y, font_size, consts::TableTextColor);
        std::ostringstream time_ss;
        time_ss << std::fixed << std::setprecision(2) << entry.time_s << "s";
        ui.draw_simple_text(window, time_ss.str(), col_time_x, y, font_size, consts::TableTextColor);
        y += y_step;
        if (++rank > consts::MaxScores) break;
    }

}

} // namespace arkanoid
