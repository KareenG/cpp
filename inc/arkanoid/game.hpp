#pragma once

#include <SFML/Graphics.hpp>

#include "arkanoid/scene.hpp"
#include "arkanoid/opening_scene.hpp"
#include "arkanoid/game_scene.hpp"
#include "arkanoid/high_scores.hpp"
#include "arkanoid/ui.hpp"

namespace arkanoid {

class Game {
public:
    Game(sf::Vector2u window_size = consts::ArkanoidWindowSize, const std::string& title = "Arkanoid");
    void run(int target_fps = 60);

private:
    void process_events();
    void update(sf::Time dt);
    void render();
    void switch_scene(scene::SceneID id);

    sf::RenderWindow window_;
    std::unique_ptr<scene::Scene> scene_;
    HighScoreTable top_scores_;
    //UI ui_; // For overlays or UI outside of scenes if needed
};

} // namespace arkanoid