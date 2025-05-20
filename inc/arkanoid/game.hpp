#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "arkanoid/scene.hpp"
#include "arkanoid/opening_scene.hpp"
#include "arkanoid/game_scene.hpp"
#include "arkanoid/high_scores.hpp"
#include "arkanoid/ui.hpp"
#include "arkanoid/top10_scene.hpp"
#include "arkanoid/high_scores.hpp"

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
    void load_and_play_music();

    sf::RenderWindow window_;
    std::unique_ptr<scene::Scene> scene_;
    UI ui_;
    bool music_muted_;
    std::unique_ptr<HighScoreTable> top_scores_;
    sf::Music background_music_;
    
};

} // namespace arkanoid