#include "SpatialGrid.hpp"

#include <algorithm>
#include <cmath>

SpatialGrid::SpatialGrid(const sf::RenderWindow& window) : window(window) {
    cell_size = 10.f;

    auto window_size = window.getSize();

    rows = static_cast<int>(
        std::ceil(static_cast<float>(window_size.y) / cell_size));
    columns = static_cast<int>(
        std::ceil(static_cast<float>(window_size.x) / cell_size));

    cells.resize(rows, std::vector<Cell>(columns));

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            cells[row][col].position = {col, row};
        }
    }
}

sf::Vector2i SpatialGrid::GetCellPosition(sf::Vector2f pixel_position) const {
    return {static_cast<int>(pixel_position.x / cell_size),
            static_cast<int>(pixel_position.y / cell_size)};
}

SpatialGrid::Cell& SpatialGrid::GetCellByOccupant(const WorldObject& occupant) {
    sf::Vector2i cell_position = GetCellPosition(occupant.GetPosition());
    Cell& cell = cells[cell_position.y][cell_position.x];
    return cell;
}

void SpatialGrid::AddOccupant(WorldObject& occupant) {
    Cell& cell = GetCellByOccupant(occupant);
    cell.occupants.push_back(&occupant);
}

void SpatialGrid::RemoveOccupant(WorldObject& occupant,
                                 sf::Vector2i cell_position) {
    Cell& cell = cells[cell_position.y][cell_position.x];
    auto it =
        std::find(cell.occupants.begin(), cell.occupants.end(), &occupant);
    if (it != cell.occupants.end()) {
        cell.occupants.erase(it);
    }
}

// Check proposed position for neighbors that violate avoidance_padding.
bool SpatialGrid::WouldCollide(const WorldObject& occupant,
                               sf::Vector2f position) {
    auto bounds = occupant.GetBounds();
    float radius = std::max(bounds.size.x, bounds.size.y) / 2.f;
    float min_distance = (radius * 2.f) + avoidance_padding;

    int cell_distance = static_cast<int>(std::ceil(min_distance / cell_size));

    const sf::Vector2i cell_position = GetCellPosition(position);

    for (int y = cell_position.y - cell_distance;
         y <= cell_position.y + cell_distance; ++y) {
        for (int x = cell_position.x - cell_distance;
             x <= cell_position.x + cell_distance; ++x) {
            // Don't access cells outside the grid.
            if (y < 0 || y >= rows || x < 0 || x >= columns) {
                continue;
            }

            const Cell& cell = cells[y][x];

            for (const WorldObject* other : cell.occupants) {
                // Don't compare the Lumie with itself.
                if (other == &occupant) {
                    continue;
                }

                sf::Vector2f difference = other->GetPosition() - position;
                if (difference.length() < min_distance) {
                    return true;
                }
            }
        }
    }
    return false;
}