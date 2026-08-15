#include <SFML/Graphics.hpp>
#include <optional>

#include "World.hpp"

int main() {
    // sf::Color background_color(38, 30, 42); // dark background
    sf::Color background_color(248, 244, 236);  // light background

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({800, 800}), "Lumera",
                            sf::Style::Default, sf::State::Windowed, settings);

    window.setFramerateLimit(50);

    World world(window);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* key_pressed =
                    event->getIf<sf::Event::KeyPressed>()) {
                if (key_pressed->scancode == sf::Keyboard::Scancode::Space) {
                    world.TogglePause();
                }
            }
        }

        window.clear(background_color);

        world.Update();
        world.Draw();

        window.display();
    }
}
