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
    sf::Vector2i cell_position = GetCellPosition(occupant.GetBounds().position);
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

bool SpatialGrid::IsOccupied(const WorldObject& occupant,
                             sf::Vector2f position) {
    const sf::Vector2i cell_position = GetCellPosition(position);
    const Cell& cell = cells[cell_position.y][cell_position.x];

    const int occupant_count = cell.occupants.size();
    if ((occupant_count == 1) && (cell.occupants[0] != &occupant) ||
        (occupant_count > 1)) {
        return true;
    }
    return false;
}