#pragma once

#include "arkanoid/scene.hpp"
#include "arkanoid/game_board.hpp"
#include "arkanoid/player.hpp"

namespace arkanoid {
namespace scene {

class GameScene : public Scene {
public:
    GameScene(GameBoard* board, Player* player, const std::string& font_path = "arial.ttf");

    SceneEvent handle_events(sf::RenderWindow& window, std::optional<sf::Event> const& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) const override;

    SceneID get_next_scene() const override;

private:
    GameBoard* board_;
    Player* player_;

    sf::Font font_;
    sf::Text score_text_;
    sf::Text lives_text_;

    bool game_started_ = false;
    bool paused_ = false;
    bool ball_fell_down_ = false;

    bool show_game_over_text_ = false;
    float game_over_timer_ = 0.f;

    bool show_win_text_ = false;
    float win_timer_ = 0.f;

    SceneID next_scene_ = SceneID::None;

    void setup_input_bindings();
    void draw_lives(sf::RenderWindow& window) const;
};

} // namespace scene
} // namespace arkanoid