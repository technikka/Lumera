#include <SFML/Graphics.hpp>
#include <optional>

#include "Creature.hpp"
#include "PerlinNoise.hpp"
#include "SpatialGrid.hpp"

int main() {
    bool paused = false;

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({800, 800}), "Lumera",
                            sf::Style::Default, sf::State::Windowed, settings);

    window.setFramerateLimit(50);

    auto window_size = window.getSize();
    sf::Vector2f center_position = {window_size.x / 2.f, window_size.y / 2.f};

    const int max_steps = 5000;
    const int creature_count = 10;

    std::vector<Creature> creatures;

    for (int i = 0; i < creature_count; ++i) {
        // emplace_back creates the object as it adds to end of vector.
        creatures.emplace_back(7.f, window_size);
    }

    SpatialGrid spatial_grid(window);

    for (auto& creature : creatures) {
        spatial_grid.AddOccupant(creature);
    }

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* key_pressed =
                    event->getIf<sf::Event::KeyPressed>()) {
                if (key_pressed->scancode == sf::Keyboard::Scancode::Space) {
                    paused = !paused;
                }
            }
        }

        window.clear(sf::Color::White);

        int step_count = 0;

        if (!paused && step_count < max_steps) {
            for (auto& creature : creatures) {
                sf::Vector2f next_position =
                    creature.GetNextPosition(window_size);

                do {
                    next_position = creature.GetNextPosition(window_size);
                } while (spatial_grid.IsOccupied(creature, next_position));

                sf::Vector2i old_cell =
                    spatial_grid.GetCellPosition(creature.GetBounds().position);

                creature.MoveTo(next_position);

                sf::Vector2i new_cell =
                    spatial_grid.GetCellPosition(creature.GetBounds().position);

                if (new_cell != old_cell) {
                    spatial_grid.RemoveOccupant(creature, old_cell);
                    spatial_grid.AddOccupant(creature);
                }
            }

            ++step_count;
        }

        // Keep update and render separate architecture
        for (const auto& creature : creatures) {
            creature.Draw(window);
        }

        window.display();
    }
}
