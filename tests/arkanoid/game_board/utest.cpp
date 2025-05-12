#include <SFML/Graphics.hpp>

#include "arkanoid/game_board.hpp"

int main() {
    const sf::Vector2u window_size{800, 600};
    sf::RenderWindow window(sf::VideoMode(window_size), "Arkanoid GameBoard Demo");
    window.setFramerateLimit(60);

    const sf::Vector2f box_size{760.f, 560.f};

    arkanoid::GameBoard board(box_size, window_size.x);

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }   
        }

        float dt = 1.f / 60.f;

        board.update(dt);

        window.clear(sf::Color::Black);
        board.draw(window);
        window.display();
    }
}
