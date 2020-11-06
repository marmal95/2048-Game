#pragma once

#include "tile.hpp"
#include "defs.hpp"

struct Animated
{
	Tile animatedTile{};
	Tile& targetTile;
	Direction direction{};
	float leftTime{ ANIMATION_TIME };
};