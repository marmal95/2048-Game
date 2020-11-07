#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <unordered_map>
#include "tile_type.hpp"

const auto WINDOW_SIZE = sf::Vector2i{ 600, 600 };
const auto GRID_SIZE = sf::Vector2f{ 500, 500 };
const auto GRID_DIMENSION = sf::Vector2i{ 4, 4 };
const auto TILE_SIZE = sf::Vector2f{ 122.5, 122.5 };
const auto TILE_MARGIN = sf::Vector2f{ 2, 2 };

const auto BACKGROUND_COLOR = sf::Color(250, 248, 239);
const auto GRID_COLOR = sf::Color(187, 173, 160);

const auto ANIMATION_TIME = 0.1f; // seconds

const std::unordered_map<TileType, sf::Color> TILES_COLORS
{
	{ TileType::BLANK, sf::Color(205, 193, 180) },
	{ TileType::VALUE_2, sf::Color(238, 228, 218) },
	{ TileType::VALUE_4, sf::Color(238, 225, 201) },
	{ TileType::VALUE_8, sf::Color(243, 178, 122) },
	{ TileType::VALUE_16, sf::Color(246, 150, 100) },
	{ TileType::VALUE_32, sf::Color(247, 124, 95) },
	{ TileType::VALUE_64, sf::Color(247, 95, 59) },
	{ TileType::VALUE_128, sf::Color(237, 208, 115) },
	{ TileType::VALUE_256, sf::Color(237, 204, 98) },
	{ TileType::VALUE_512, sf::Color(237, 201, 80) },
	{ TileType::VALUE_1024, sf::Color(237, 193, 63) },
	{ TileType::VALUE_2048, sf::Color(237, 194, 46) },
};

const std::unordered_map<TileType, sf::Color> FONT_COLORS
{
	{ TileType::VALUE_2, sf::Color(119, 110, 101) },
	{ TileType::VALUE_4, sf::Color(119, 110, 101) },
	{ TileType::VALUE_8, sf::Color(255, 255, 255) },
	{ TileType::VALUE_16, sf::Color(255, 255, 255) },
	{ TileType::VALUE_32, sf::Color(255, 255, 255) },
	{ TileType::VALUE_64, sf::Color(255, 255, 255) },
	{ TileType::VALUE_128, sf::Color(255, 255, 255) },
	{ TileType::VALUE_256, sf::Color(255, 255, 255) },
	{ TileType::VALUE_512, sf::Color(255, 255, 255) },
	{ TileType::VALUE_1024, sf::Color(255, 255, 255) },
	{ TileType::VALUE_2048, sf::Color(255, 255, 255) }
};

const std::unordered_map<TileType, uint32_t> FONT_SIZES
{
	{ TileType::BLANK, 0 },
	{ TileType::VALUE_2, 64 },
	{ TileType::VALUE_4, 64 },
	{ TileType::VALUE_8, 64 },
	{ TileType::VALUE_16, 56 },
	{ TileType::VALUE_32, 56 },
	{ TileType::VALUE_64, 56 },
	{ TileType::VALUE_128, 48 },
	{ TileType::VALUE_256, 48 },
	{ TileType::VALUE_512, 48 },
	{ TileType::VALUE_1024, 42 },
	{ TileType::VALUE_2048, 42 }
};

enum class Direction
{
	None,
	Left,
	Up,
	Down,
	Right
};