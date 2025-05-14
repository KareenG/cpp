#include "arkanoid/level.hpp"
#include <sstream>

namespace arkanoid::level {

static const std::unordered_map<char, sf::Color> color_map = {
    {'R', sf::Color::Red},
    {'G', sf::Color::Green},
    {'B', sf::Color::Blue},
    {'Y', sf::Color::Yellow},
    {'C', sf::Color::Cyan},
    {'M', sf::Color::Magenta},
    {'W', sf::Color::White},
    {'O', sf::Color(255, 165, 0)} // Orange
};

sf::Color get_color(char c, int row = 0) {
    auto it = color_map.find(c);
    if (it != color_map.end()) return it->second;
    // fallback: color by row if c is not mapped
    static const std::vector<sf::Color> row_colors = {
        sf::Color::Red, sf::Color::Green, sf::Color::Blue,
        sf::Color::Yellow, sf::Color::Cyan, sf::Color::Magenta
    };
    return row_colors[row % row_colors.size()];
}

// Pre-defined patterns for each level
static const std::array<std::string, 4> level_patterns = {
    // Level 1 - Simple 3 rows with different colors
    "MMMMM\n"
    "CCCCC\n"
    "YYYYY\n",

    // Level 2 - Pattern from Image 1
    "C C C C C C\n"
    "M M M M M M\n"
    "Y Y Y Y Y Y\n"
    "B B B B B B",

    // Level 3 - Pattern from Image 2 (3 columns of colors)
    "YYY WWW YYY\n"
    "MMM OOO MMM\n"
    "BBB CCC BBB\n"
    "GGG RRR GGG\n"
    "WWW YYY WWW",

    // Level 4 - Space Invader Pattern from Image 3
    " BBB BBB \n"
    "BBBBBBBBB\n"
    "BBWWWWWBB\n"
    " BWWWWWB \n"
    "  WWWWW  \n"
    "   WWW   \n"
    "   YYY   \n"
    "    Y    \n"
};

std::vector<std::unique_ptr<Brick>> load(
    int level_num,
    sf::Vector2f box_left_top_boarders,
    sf::Vector2f box_size,
    float padding_left,
    float padding_right,
    float padding_top,
    float brick_height)
{
   if(level_num == 1 || level_num == 4) {
        return util::load_grid(level_num, box_left_top_boarders, box_size, padding_left, padding_right, padding_top, brick_height);
   }
   return util::load_level_pattern_with_spaces(level_num, box_left_top_boarders, box_size, padding_left, padding_right, padding_top, brick_height);
}

std::vector<std::unique_ptr<Brick>> util::load_grid(
    int level_num,
    sf::Vector2f box_left_top_boarders,
    sf::Vector2f box_size,
    float padding_left,
    float padding_right,
    float padding_top,
    float brick_height
) {
    std::vector<std::unique_ptr<Brick>> bricks;
    
    // Adjust level_num (user levels start at 1, but our array is 0-indexed)
    --level_num;
    
    // Check if level_num is valid
    if (level_num < 0 || level_num >= static_cast<int>(level_patterns.size())) {
        return bricks; // Return empty bricks if invalid level
    }
    
    // Get the pattern for the specified level
    std::string pattern = level_patterns[level_num];
    
    // Calculate pattern dimensions
    std::istringstream ss(pattern);
    int max_width = 0;
    int height = 0;
    std::string line;
    std::vector<std::string> lines;
    
    while (std::getline(ss, line)) {
        lines.push_back(line);
        max_width = std::max(max_width, static_cast<int>(line.size()));
        height++;
    }
    
    // Brick thickness constant
    const float brick_thickness = 1.0f;
    
    // Calculate usable width and brick width
    // Account for the thickness of borders (total thickness per row = number of bricks * thickness)
    float usable_width = box_size.x - padding_left - padding_right - 2*(max_width * brick_thickness);
    float brick_width = usable_width / max_width;
    
    // If pattern is too tall, adjust brick height to fit
    // Also account for brick thickness in height calculation
    float usable_height = box_size.y - padding_top - padding_top - (height * brick_thickness);
    if (height * brick_height > usable_height) {
        brick_height = usable_height / height;
    }
    
    float start_x = box_left_top_boarders.x + padding_left + brick_thickness + (brick_width )/2;
    float start_y = box_left_top_boarders.y + padding_top;
    
    // Create bricks
    for (int row = 0; row < height; ++row) {
        const std::string& current_line = lines[row];
        for (size_t col = 0; col < current_line.size(); ++col) {
            char c = current_line[col];
            if (c == ' ' || c == '.') continue;
            
            // Account for brick thickness in position calculation
            sf::Vector2f pos(
                start_x + col * (brick_width + brick_thickness),
                start_y + row * (brick_height + 2*brick_thickness)
            );
            
            sf::Vector2f size(brick_width, brick_height);
            sf::Color color = get_color(c, row);
            bricks.push_back(std::make_unique<Brick>(size, pos, color));
        }
    }
    
    return bricks;
}

std::vector<std::unique_ptr<Brick>> util::load_level_pattern_with_spaces(
    int level_num,
    sf::Vector2f box_left_top_boarders,
    sf::Vector2f box_size,
    float padding_left,
    float padding_right,
    float padding_top,
    float brick_height
) {
    std::vector<std::unique_ptr<Brick>> bricks;

    --level_num;
    if (level_num < 0 || level_num >= static_cast<int>(level_patterns.size())) {
        return bricks;
    }

    std::string pattern = level_patterns[level_num];

    std::istringstream ss(pattern);
    std::vector<std::string> lines;
    int max_bricks = 0;
    int max_spaces = 0;
    std::string line;

    // Count max bricks and horizontal space runs
    while (std::getline(ss, line)) {
        lines.push_back(line);

        int bricks_in_line = 0;
        int spaces_in_line = 0;
        bool in_space = false;

        for (char c : line) {
            if (c == ' ' || c == '.') {
                if (!in_space) {
                    ++spaces_in_line;
                    in_space = true;
                }
            } else {
                ++bricks_in_line;
                in_space = false;
            }
        }

        max_bricks = std::max(max_bricks, bricks_in_line);
        max_spaces = std::max(max_spaces, spaces_in_line);
    }

    int height = static_cast<int>(lines.size());

    const float brick_thickness = 1.0f;
    const float space_width = 36.0f;
    const float space_height = 4.0f;

    float usable_width = box_size.x - padding_left - padding_right - 2*(max_bricks * brick_thickness);
    float brick_width = (usable_width - (max_spaces * space_width)) / max_bricks;

    // Count how many blank lines (rows with only spaces/dots)
    int blank_rows = 0;
    for (const std::string& row_line : lines) {
        bool is_blank = true;
        for (char c : row_line) {
            if (c != ' ' && c != '.') {
                is_blank = false;
                break;
            }
        }
        if (is_blank)
            ++blank_rows;
    }

    // Adjust vertical height to fit
    float usable_height = box_size.y - 2 * padding_top - (height * brick_thickness) - (blank_rows * space_height);
    if (height * brick_height > usable_height)
        brick_height = usable_height / height;

    float start_y = box_left_top_boarders.y + padding_top;
    float y = start_y;

    for (int row = 0; row < height; ++row) {
        const std::string& current_line = lines[row];

        // Determine if the row is blank (affects y spacing)
        bool is_blank_row = true;
        for (char c : current_line) {
            if (c != ' ' && c != '.') {
                is_blank_row = false;
                break;
            }
        }

        if (is_blank_row) {
            y += space_height + brick_thickness; // no row content
            continue;
        }

        float x = box_left_top_boarders.x + padding_left + brick_thickness;// + brick_thickness;
        bool in_space = false;

        for (char c : current_line) {
            if (c == ' ' || c == '.') {
                if (!in_space) {
                    x += space_width;
                    in_space = true;
                }
                continue;
            }

            in_space = false;

            sf::Vector2f pos(x + brick_thickness + brick_width / 2.0f, y);
            sf::Vector2f size(brick_width, brick_height);
            sf::Color color = get_color(c, row);
            bricks.push_back(std::make_unique<Brick>(size, pos, color));

            x += brick_width + brick_thickness;
        }

        y += brick_height + 2 * brick_thickness;
    }

    return bricks;
}

} // namespace arkanoid::level
