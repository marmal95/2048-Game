#pragma once

#include "grid.hpp"

namespace TilePositionFinder
{
    std::size_t findDown(const std::size_t sourcePosition, const std::size_t columnIndex, const Tile& srcTile, const std::vector<std::vector<Tile>>& tiles)
    {
        std::size_t targetPosition = sourcePosition;

        while ((targetPosition + 1) < GRID_DIMENSION.x)
        {
            if (tiles[targetPosition + 1][columnIndex].getType() == TileType::BLANK)
            {
                ++targetPosition;
            }
            else if (tiles[targetPosition + 1][columnIndex].getType() == srcTile.getType() && tiles[targetPosition + 1][columnIndex].isMergeable())
            {
                ++targetPosition;
                break;
            }
            else
            {
                break;
            }
        }

        return targetPosition;
    }

    std::size_t findRight(const std::size_t sourcePosition, const std::size_t rowIndex, const Tile& srcTile, const std::vector<std::vector<Tile>>& tiles)
    {
        std::size_t targetPosition = sourcePosition;

        while ((targetPosition + 1) < GRID_DIMENSION.y)
        {
            if (tiles[rowIndex][targetPosition + 1].getType() == TileType::BLANK)
            {
                ++targetPosition;
            }
            else if (tiles[rowIndex][targetPosition + 1].getType() == srcTile.getType() && tiles[rowIndex][targetPosition + 1].isMergeable())
            {
                ++targetPosition;
                break;
            }
            else
                break;
        }

        return targetPosition;
    }

    std::size_t findLeft(const std::size_t sourcePosition, const std::size_t rowIndex, const Tile& srcTile, const std::vector<std::vector<Tile>>& tiles)
    {
        std::size_t targetPosition = sourcePosition;

        while (targetPosition > 0)
        {
            if (tiles[rowIndex][targetPosition - 1].getType() == TileType::BLANK)
            {
                --targetPosition;
            }
            else if (tiles[rowIndex][targetPosition - 1].getType() == srcTile.getType() && tiles[rowIndex][targetPosition - 1].isMergeable())
            {
                --targetPosition;
                break;
            }
            else
                break;
        }

        return targetPosition;
    }

    std::size_t findUp(const std::size_t sourcePosition, const std::size_t columnIndex, const Tile& srcTile, const std::vector<std::vector<Tile>>& tiles)
    {
        std::size_t targetPosition = sourcePosition;

        while (targetPosition > 0)
        {
            if (tiles[targetPosition - 1][columnIndex].getType() == TileType::BLANK)
            {
                --targetPosition;
            }
            else if (tiles[targetPosition - 1][columnIndex].getType() == srcTile.getType() && tiles[targetPosition - 1][columnIndex].isMergeable())
            {
                --targetPosition;
                break;
            }
            else
                break;
        }

        return targetPosition;
    }
}