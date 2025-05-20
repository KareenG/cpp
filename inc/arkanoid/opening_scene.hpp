#pragma once

#include <SFML/Graphics.hpp>

#include "arkanoid/scene.hpp"
#include "arkanoid/button.hpp"
#include "arkanoid/ui.hpp"

namespace arkanoid::scene {

class OpeningScene : public Scene {
public:
    OpeningScene(sf::RenderWindow& window, const UI& ui);

    SceneEvent handle_events(sf::RenderWindow& window, std::optional<sf::Event> const& event) override;
    void update(float dt) override;//SceneResult
    void render(sf::RenderWindow& window) const override;
    SceneID get_next_scene() const override;

private:
    const sf::Texture& background_texture_;
    sf::Sprite background_sprite_;

    const UI& ui_;
    //const sf::Font& font_;

    Button play_button_;
    Button top10_button_;
    Button quit_button_;

    SceneID next_scene_ = SceneID::None;
};

} // namespace arkanoid::scene
