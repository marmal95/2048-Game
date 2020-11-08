#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include "tile.hpp"
#include "defs.hpp"


class Grid
{
public:
    Grid();

private:
    void prepareGrid();
    void prepareTiles();
    sf::Vector2f getTopLeftCornerPosition() const;

    sf::RectangleShape grid;
    std::vector<std::vector<Tile>> tiles;

    friend class LogicSystem;
    friend class DrawSystem;
};