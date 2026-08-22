#pragma once

#include "Deltaframe.hpp"
#include "Lumie.hpp"
#include "Seekra.hpp"
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
    sf::Vector2u window_size = window.getSize();
    SpatialGrid spatial_grid;
    std::vector<Lumie> lumies;
    Seekra seekra;
    Deltaframe deltaframe;

    void InitializeLumies();
    void UpdateLumies();
};
