#pragma once

#include "tile.hpp"
#include "defs.hpp"

struct MoveTrigger
{
    MoveTrigger(const Tile& srcTile, Tile& tgtTile, const Direction direction)
        : srcTile{ srcTile }, tgtTile{ tgtTile }, direction{ direction } {}

    Tile srcTile{};
    Tile& tgtTile;
    Direction direction{};
};