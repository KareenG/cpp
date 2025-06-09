#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "arkanoid/scene.hpp"
#include "arkanoid/game_board.hpp"
#include "arkanoid/player.hpp"
#include "arkanoid/resources_and_consts.hpp"
#include "arkanoid/input_controller.hpp"
#include "arkanoid/ui.hpp"
#include "arkanoid/game_logic.hpp"
#include "arkanoid/overlay_layer.hpp"
#include "arkanoid/input_name.hpp"
#include "arkanoid/high_scores.hpp"
#include "arkanoid/level_loader.hpp"

namespace arkanoid {
    
namespace scene {

// enum class SceneResult {
//     None,
//     BallFell,
//     BrickHit,
//     LevelComplete
// };

class GameScene : public Scene {
    using NameInputCallback = std::function<void(int score, float time, std::function<void(const std::string&)>)>;

public:
    GameScene(HighScoreTable* high_scores, const UI& ui);//, int num_level = 1, const std::string& font_path = consts::FontArial);

    SceneEvent handle_events(sf::RenderWindow& window, std::optional<sf::Event> const& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) const override;

    SceneID get_next_scene() const override;

    int get_level() const;

    void set_name_input_callback(NameInputCallback cb);

private:
    void finish_scene(SceneID next);
    void setup_input_bindings();
    void reset_level();

private:
    LevelLoader level_loader_;
    GameBoard board_;
    Player player_;
    size_t num_level_;
    const UI& ui_;
    //sf::Font font_;
    InputController input_controller_;
    // UI ui_;
    GameLogic logic_;
    OverlayLayer overlay_;
    NameEntryDialog name_input_;
    HighScoreTable* high_scores_;

    bool started_ = false;
    bool paused_ = false;
    bool ball_fell_down_ = false;

    NameInputCallback on_name_input_requested_;

    SceneID next_scene_ = SceneID::None;
};

} // namespace scene

} // namespace arkanoid