#include "grid.hpp"
#include "defs.hpp"

Grid::Grid()
    : grid{}, tiles{}
{
    prepareGrid();
    prepareTiles();
}

void Grid::setPosition(const sf::Vector2f& position)
{
    Transformable::setPosition(position);
    grid.setPosition(position);
    setTilesPosition(position);
}

void Grid::prepareGrid()
{
    grid.setSize(GRID_SIZE);
    grid.setFillColor(GRID_COLOR);
}

void Grid::prepareTiles()
{
    const auto gridPosition = getPosition();

    for (int j = 0; j < GRID_DIMENSION.y; j++)
    {
        std::vector<Tile> gridRow{};

        for (int i = 0; i < GRID_DIMENSION.x; i++)
        {
            gridRow.emplace_back();
        }
        tiles.push_back(std::move(gridRow));
    }
}

void Grid::setTilesPosition(const sf::Vector2f& position)
{
    for (int i = 0; i < GRID_DIMENSION.y; i++)
    {
        for (int j = 0; j < GRID_DIMENSION.x; j++)
        {
            tiles[i][j].setPosition({ position.x + j * TILE_SIZE.x + TILE_MARGIN.x * (j + 1),
                                      position.y + i * TILE_SIZE.y + TILE_MARGIN.y * (i + 1) });
        }
    }
}
