#pragma once

#include <SFML/Graphics.hpp>

#include "WorldObject.hpp"

class SpatialGrid {
   public:
    SpatialGrid(const sf::RenderWindow& window);
    sf::Vector2i GetCellPosition(sf::Vector2f position) const;
    bool IsOccupied(const WorldObject& occupant, sf::Vector2f position);

    struct Cell {
        sf::Vector2i position;
        std::vector<WorldObject*> occupants;
    };

    void AddOccupant(WorldObject& occupant);
    void RemoveOccupant(WorldObject& occupant, sf::Vector2i cell_position);

   private:
    int rows;
    int columns;
    float cell_size;

    std::vector<std::vector<Cell>> cells;

    const sf::RenderWindow& window;

    Cell& GetCellByOccupant(const WorldObject& occupant);
};
