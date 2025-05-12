#include "arkanoid/game_board.hpp"
#include "arkanoid/level.hpp"

namespace arkanoid {

// ─── Static Layout Constants ─────────────────────────────
static constexpr float kOffsetLeft   = 40.f;
static constexpr float kOffsetRight  = 40.f;
static constexpr float kOffsetTop    = 90.f;
static constexpr float kOffsetBottom = 60.f;
static constexpr float kBrickSpacing = 5.f;
static constexpr int kBrickCols      = 5;
static constexpr int kBrickRows      = 3;
static constexpr float kBrickHeight  = 30.f;
static constexpr float kPaddleHeight = 20.f;
static constexpr float kBallRadius   = 10.f;
static constexpr sf::Color gray{128, 128, 128}; // Medium gray


GameBoard::GameBoard(sf::Vector2f const& box_size, int level_num)
: box_({20.f, 20.f}, box_size, sf::Color::Black, sf::Color::White)
, paddle_(
    sf::Vector2f{100.f, kPaddleHeight},
    sf::Vector2f{
        box_.get_position().x + box_.get_size().x / 2.f,
        box_.get_position().y + box_.get_size().y - kPaddleHeight / 2.f - kOffsetBottom
    },
    gray,
    350.f
)
, ball_(
    sf::Vector2f{
        box_.get_position().x + box_.get_size().x / 2.f,
        paddle_.get_position().y - kPaddleHeight / 2.f - kBallRadius - 1.f
    },
    kBallRadius,
    {0.f, 0.f},  // ← static velocity
    sf::Color::White
)
{
    // ─── Brick Layout Calculation ─────────────────────────────

    const float usable_width = box_.get_size().x - kOffsetLeft - kOffsetRight;
    const float brick_width = usable_width / kBrickCols;

    bricks_ = level::load_grid(
        kBrickRows,
        kBrickCols,
        sf::Vector2f{
            //box_.get_position().x + kOffsetLeft,
            130.f,
            box_.get_position().y + kOffsetTop
        },
        {brick_width, kBrickHeight},
        0.f, // no spacing between bricks
        level_num
    );
}


void GameBoard::update(float dt)
{
    paddle_.update(dt);
    ball_.update(dt);
}

void GameBoard::draw(sf::RenderWindow& window) const
{
    box_.draw(window);
    for (const auto& brick : bricks_)
        brick.draw(window);
    paddle_.draw(window);
    ball_.draw(window);
}

const Box& GameBoard::box() const
{
    return box_;
}

Paddle& GameBoard::paddle()
{
    return paddle_;
}

Ball& GameBoard::ball()
{
    return ball_;
}

const std::vector<Brick>& GameBoard::bricks() const
{
    return bricks_;
}

} // namespace arkanoid