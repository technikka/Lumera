#include <SFML/Graphics.hpp>

#include "PerlinNoise.hpp"
#include "SpatialGrid.hpp"
#include "World.hpp"

World::World(sf::RenderWindow& window) : window(window), spatial_grid(window) {
    InitializeLumies();
}

const int max_steps = 5000;

void World::InitializeLumies() {
    for (int i = 0; i < lumie_count; ++i) {
        // emplace_back creates the object as it adds to end of vector.
        lumies.emplace_back(window.getSize());
    }

    for (auto& lumie : lumies) {
        spatial_grid.AddOccupant(lumie);
    }
}

void World::UpdateLumies() {
    sf::Vector2u window_size = window.getSize();
    for (auto& lumie : lumies) {
        sf::Vector2f next_position;

        do {
            next_position = lumie.GetNextPosition(window_size);
        } while (spatial_grid.WouldCollide(lumie, next_position));

        sf::Vector2i old_cell =
            spatial_grid.GetCellPosition(lumie.GetPosition());

        lumie.MoveTo(next_position);

        sf::Vector2i new_cell =
            spatial_grid.GetCellPosition(lumie.GetPosition());

        if (new_cell != old_cell) {
            spatial_grid.RemoveOccupant(lumie, old_cell);
            spatial_grid.AddOccupant(lumie);
        }
    }
}

void World::Update() {
    if (!paused) {
        UpdateLumies();
    }
}

void World::Draw() {
    for (const auto& lumie : lumies) {
        lumie.Draw(window);
    }
}

void World::TogglePause() { paused = !paused; }