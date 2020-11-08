#include "grid.hpp"
#include "defs.hpp"

Grid::Grid()
    : grid{}, tiles{}
{
    prepareGrid();
    prepareTiles();
}

void Grid::prepareGrid()
{
    grid.setSize(GRID_SIZE);
    grid.setFillColor(GRID_COLOR);
    grid.setOrigin(GRID_SIZE.x / 2.f, GRID_SIZE.y / 2.f);
    grid.setPosition(WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y / 2.f);
}

void Grid::prepareTiles()
{
    const auto topLeftGridCorner = getTopLeftCornerPosition();

    for (int j = 0; j < GRID_DIMENSION.y; j++)
    {
        std::vector<Tile> gridRow{};

        for (int i = 0; i < GRID_DIMENSION.x; i++)
        {
            Tile tile{};
            tile.setOrigin(topLeftGridCorner);
            tile.setPosition({ i * TILE_SIZE.x + TILE_MARGIN.x * (i + 1), j * TILE_SIZE.y + TILE_MARGIN.y * (j + 1) });
            gridRow.push_back(std::move(tile));
        }
        tiles.push_back(std::move(gridRow));
    }
}

sf::Vector2f Grid::getTopLeftCornerPosition() const
{
    return { grid.getOrigin().x - grid.getPosition().x, grid.getOrigin().y - grid.getPosition().y };
}
