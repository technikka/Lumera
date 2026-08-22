#include <SFML/Graphics.hpp>

#include "Deltaframe.hpp"
#include "PerlinNoise.hpp"
#include "Seekra.hpp"
#include "SpatialGrid.hpp"
#include "World.hpp"

World::World(sf::RenderWindow& window)
    : window(window),
      spatial_grid(window),
      seekra(window_size),
      deltaframe(window_size) {
    InitializeLumies();
}

void World::InitializeLumies() {
    for (int i = 0; i < lumie_count; ++i) {
        // emplace_back creates the object as it adds to end of vector.
        lumies.emplace_back(window_size);
    }

    for (auto& lumie : lumies) {
        spatial_grid.AddOccupant(lumie);
    }
}

void World::UpdateLumies() {
    constexpr int max_attempts = 10;
    bool can_move = false;

    for (auto& lumie : lumies) {
        sf::Vector2f next_position;

        for (int attempt = 0; attempt < max_attempts; ++attempt) {
            next_position = lumie.GetNextPosition(window_size);
            if (!spatial_grid.WouldCollide(lumie, next_position)) {
                can_move = true;
                break;
            }
        }
        if (!can_move) {
            continue;
        }

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
        seekra.Move();
        deltaframe.Update();
    }
}

void World::Draw() {
    seekra.Draw(window);
    for (const auto& lumie : lumies) {
        lumie.Draw(window);
    }
    deltaframe.Draw(window);
}

void World::TogglePause() { paused = !paused; }