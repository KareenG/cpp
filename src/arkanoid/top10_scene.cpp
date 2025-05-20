#include "arkanoid/top10_scene.hpp"

namespace arkanoid::scene {

Top10Scene::Top10Scene(sf::RenderWindow& window, const HighScoreTable* high_scores, const UI& ui)
: window_(window)
, high_scores_(high_scores)
, ui_(ui)
, background_{resources::get_texture(consts::TextureTopTen)}
{
}

SceneEvent Top10Scene::handle_events(sf::RenderWindow& window, std::optional<sf::Event> const& event)
{
    (void) window;
    if (!event.has_value()) {
        return SceneEvent::None;
    }
    if (event->is<sf::Event::Closed>()) {
        return SceneEvent::QuitScene;
    }
    // Any key brings back to opening
    if (event.has_value() &&
        (event->is<sf::Event::KeyPressed>() || event->is<sf::Event::TextEntered>() || event->is<sf::Event::MouseButtonPressed>())) {
        notify_scene_change(SceneID::Opening);
    }

    return SceneEvent::None;
}

void Top10Scene::update(float)
{// No animations for now
} 

void Top10Scene::render(sf::RenderWindow& window) const
{
    window.clear(sf::Color::Black);
    window_.draw(background_);
    // Title
    ui_.draw_centered_text(window, consts::Top10Title, consts::Top10TitleColor, consts::Top10TitleSize, consts::Top10TitleYOffset);

    high_scores_->render(window, ui_);
}

} // namespace arkanoid::scene
