#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "arkanoid/scene.hpp"
#include "arkanoid/game_scene.hpp"
#include "arkanoid/game_board.hpp"
#include "arkanoid/player.hpp"

namespace arkanoid {

class Game {
public:
    Game(sf::Vector2u window_size = {800, 600}, const std::string& title = "Arkanoid");
    void run(int target_fps = 60);

private:
    void process_events();
    void update(sf::Time dt);
    void render();

private:
    sf::RenderWindow window_;

    Player player_;
    GameBoard board_;
    std::unique_ptr<scene::Scene> scene_;
    bool paused_{false};
    int current_level{1};

    scene::SceneID current_scene_id_ = scene::SceneID::Game; // start directly
};

} // namespace arkanoid
