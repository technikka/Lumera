#include <SFML/Graphics.hpp>
#include <optional>

#include "PerlinNoise.hpp"
#include "creature.hpp"

int main() {
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({800, 800}), "Lumera",
                            sf::Style::Default, sf::State::Windowed, settings);

    auto window_size = window.getSize();
    // Calculate center to pass in to Creature position
    Creature creature(5.f, {window_size.x / 2.f, window_size.y / 2.f});

    const int max_steps = 5000;
    int step_count = 0;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        window.clear(sf::Color::White);
        creature.Draw(window);

        if (step_count < max_steps) {
            creature.Move(window_size);
            ++step_count;
        }

        window.display();
    }
}
