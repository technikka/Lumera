#pragma once

#include "Lumie.hpp"
#include "Mover.hpp"
#include "SpatialGrid.hpp"

class World {
   public:
    World(sf::RenderWindow& window);
    void TogglePause();
    void Update();
    void Draw();

   private:
    bool paused = false;
    const int lumie_count = 20;
    sf::RenderWindow& window;
    SpatialGrid spatial_grid;
    std::vector<Lumie> lumies;
    Mover mover;

    void InitializeLumies();
    void UpdateLumies();
};
