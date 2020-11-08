#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include "tile.hpp"
#include "defs.hpp"


class Grid : public sf::Transformable
{
public:
    Grid();
    void setPosition(const sf::Vector2f&);

private:
    void prepareGrid();
    void prepareTiles();
    void setTilesPosition(const sf::Vector2f&);

    sf::RectangleShape grid;
    std::vector<std::vector<Tile>> tiles;

    friend class LogicSystem;
    friend class DrawSystem;
};