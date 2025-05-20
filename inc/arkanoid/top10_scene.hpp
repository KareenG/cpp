#pragma once

#include <SFML/Graphics.hpp>

#include "arkanoid/high_scores.hpp"
#include "arkanoid/ui.hpp"
#include "arkanoid/resources_and_consts.hpp"
#include "arkanoid/scene.hpp"

namespace arkanoid::scene {

class Top10Scene : public Scene {
public:
    Top10Scene(sf::RenderWindow& window, const HighScoreTable* high_scores, const UI& ui);

    SceneEvent handle_events(sf::RenderWindow& window, std::optional<sf::Event> const& event) override;

    void update(float) override;

    void render(sf::RenderWindow& window) const override;
private:
    sf::RenderWindow& window_;
    const HighScoreTable* high_scores_;
    const UI& ui_;
    sf::Sprite background_;
};

} // namespace arkanoid::scene
