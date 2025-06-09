
#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>
#include <functional>

namespace arkanoid {

using TimeType = uint64_t;        //uint64_t 8 bytes
using ScoreType = unsigned int;   // 4 bytes
    
} // namespace arkanoid

namespace arkanoid::consts {

// Asset file paths
inline const std::string FontArial = "assets/arial.ttf";
inline const std::string TextureBackground = "assets/back_bg.png";
inline const std::string TextureBall = "assets/ball.png";
inline const std::string TextureGame = "assets/scene_bg2.jpg";//back1.png
inline const std::string TextureTopTen = "assets/top10bg.jpg";//background2
inline const std::string BackgroundMusic = "assets/intro_theme2.ogg";//intro_theme2.flac

//inline constexpr int MaxLevels = 10;
inline constexpr float OverlayDuration = 2.0f;

inline constexpr sf::Vector2u ArkanoidWindowSize = {800, 760}; // 740
inline constexpr sf::Vector2u ArkanoidBoxSize = {760, 700};
inline constexpr sf::Vector2f ArkanoidBoxPosition = {20.f, 40.f};

inline constexpr int MaxNameLength = 16;
inline constexpr int MaxScores = 10;

inline const std::string LevelsFile{"levels.dat"};

inline constexpr sf::Color Orange = sf::Color(255, 165, 0);

inline const std::unordered_map<char, sf::Color> ColorMap = {
    {'R', sf::Color(200, 0, 0)},          // Red
    {'B', sf::Color(  0,   60, 230)},      // Blue
    {'P', sf::Color(255, 192, 203)},      // Pink
    {'G', sf::Color(  0, 220,   0)},      // Green
    {'O', sf::Color(255, 165,   0)},      // Orange
    {'U', sf::Color(255, 127,  80)},      // Orange-red
    {'S', sf::Color(  0, 191, 255)},      // Sky Blue
    {'W', sf::Color(255, 255, 255)},      // White
    {'D', sf::Color(192, 192, 192)},      // Gray (dynamic score)
    {'Y', sf::Color(255, 215,   0)}       // Gold/Yellow (indestructible)
};

inline const std::unordered_map<char, int> BrickCharToScore = {
    {'R',  90},
    {'B', 100},
    {'P', 110},
    {'G',  80},
    {'O', 120},
    {'U',  60},
    {'S',  70},
    {'W',  50},
    {'D', -1},   // dynamic score (e.g., 50*level)
    {'Y',  0}    // indestructible
};

// Note: -1 means "special" score (like 50 * level).
inline constexpr int GrayBrickBaseScore = 50;

inline const std::string GameTitle{"Arkanoid"};
inline const sf::Color GameTitleColor{sf::Color::White};
inline const size_t GameTitleSize{75};
inline const float GameTitleYOffset{100.f};

inline const std::string PlayText{"Play"};
inline const size_t PlayTextSize{36};

inline const std::string Top10Text{"Top 10"};
inline const size_t Top10TextSize{36};

inline const std::string QuitText{"Quit"};
inline const size_t QuitTextSize{36};


inline const std::string Top10Title{"Top 10 players"};
inline const sf::Color Top10TitleColor{sf::Color::White};
inline const size_t Top10TitleSize{75};
inline const float Top10TitleYOffset{100.f};

// Box Layout Constants
inline constexpr float OffsetLeft   = 40.f;
inline constexpr float OffsetRight  = 40.f;
inline constexpr float OffsetTop    = 100.f;
inline constexpr float OffsetBottom = 60.f;
inline constexpr float BrickSpacing = 5.f;
inline constexpr int   BrickCols    = 5;
inline constexpr int   BrickRows    = 3;
inline constexpr float BrickHeight  = 30.f;
inline constexpr float PaddleHeight = 20.f;
inline constexpr float BallRadius   = 10.f;


static constexpr sf::Color gray{128, 128, 128}; // Medium gray
inline const sf::Color PaddleColor(255, 140, 0);

inline const size_t TableTextSize{24};
inline constexpr float OffsetYTopScoresTable = 250.f;
inline const sf::Color TableTextColor{sf::Color(220, 220, 220)};
inline const std::string NoHighScoresYetText{"No high scores yet."};
inline const std::string Top10FileName{"top10.dat"};
inline const std::string NewTop10PromptText{"Congratulations! You've made it to the Top 10!\n\nEnter your name:"};

inline constexpr int NameWidth = 32;      // ≤ 32 characters
inline constexpr int ScoreWidth = 4;
inline constexpr int TimeWidth = 8;
inline constexpr int RowWidth = NameWidth + ScoreWidth + TimeWidth;

} // namespace arkanoid::consts

namespace arkanoid::resources {

/**
 * Get a font resource from the cache or load it if not available
 * @param path Filename of the font (without directory)
 * @return Reference to the loaded font
 */
const sf::Font& get_font(const std::string& path);

/**
 * Get a texture resource from the cache or load it if not available
 * @param path Filename of the texture (without directory)
 * @return Reference to the loaded texture
 */
const sf::Texture& get_texture(const std::string& path);

/**
 * Clear all cached resources
 */
void clear();

} // namespace arkanoid::resources