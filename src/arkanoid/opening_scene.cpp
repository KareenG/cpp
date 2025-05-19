#include "arkanoid/opening_scene.hpp"
#include "arkanoid/resources_and_consts.hpp"

namespace arkanoid::scene {

OpeningScene::OpeningScene(sf::RenderWindow& window)
: background_texture_(resources::get_texture(consts::TextureBackground))
, background_sprite_(background_texture_)
, ui_(consts::FontArial)
, font_(resources::get_font(consts::FontArial))
, play_button_(font_, consts::PlayText, consts::PlayTextSize, {window.getSize().x / 2.f, 250.f})
, quit_button_(font_, consts::QuitText, consts::QuitTextSize, {window.getSize().x / 2.f, 320.f})
{
    // Button behavior
    play_button_.subscribe([this]() {
        next_scene_ = SceneID::Game;
        notify_scene_change(next_scene_);
    });
    quit_button_.subscribe([&window]() { window.close(); });
}

SceneEvent OpeningScene::handle_events(sf::RenderWindow& window, std::optional<sf::Event> const& event)
{
    play_button_.handle_event(window, *event);
    quit_button_.handle_event(window, *event);

    if (!event.has_value()) {
        return SceneEvent::None;
    }

    if (event->is<sf::Event::Closed>() ||
        (event->is<sf::Event::KeyPressed>() && 
        event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)) {
        return SceneEvent::QuitScene;
    }
    
    return SceneEvent::None;
}

void OpeningScene::update(float)
{
    // No animations yet
}

void OpeningScene::render(sf::RenderWindow& window) const
{
    window.draw(background_sprite_);
    ui_.draw_centered_text(window, consts::GameTitle, consts::GameTitleColor, consts::GameTitleSize, consts::GameTitleYOffset);
    play_button_.render(window);
    quit_button_.render(window);
}

SceneID OpeningScene::get_next_scene() const
{
    return next_scene_;
}

} // namespace arkanoid::scene
