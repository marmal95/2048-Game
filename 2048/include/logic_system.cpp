#include "logic_system.hpp"
#include "grid.hpp"
#include "move_trigger.hpp"
#include "tile_position_finder.hpp"

LogicSystem::LogicSystem()
	: generator{ std::random_device{}() }, moveEvents{}, moveFinishedEvent{}, isInitialized{}, moveAllowed{}
{}

void LogicSystem::update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt)
{
	if (not isInitialized)
		initialize(es);
	else
		update(es, events);

	moveEvents.clear();
	moveFinishedEvent.reset();
}

void LogicSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<sf::Event::KeyEvent>(*this);
	eventManager.subscribe<MoveFinished>(*this);
}

void LogicSystem::receive(const sf::Event::KeyEvent& keyEvent)
{
	if (moveAllowed)
	{
		moveEvents.push_back(keyEvent);
	}
}

void LogicSystem::receive(const MoveFinished& event)
{
	moveFinishedEvent = event;
}

void LogicSystem::initialize(entityx::EntityManager& es)
{
	isInitialized = true;
	auto gridEntity = *es.entities_with_components<Grid>().begin();
	auto gridComponent = gridEntity.component<Grid>();
	spawnRandomTile(*gridComponent);
	moveAllowed = true;
}

void LogicSystem::update(entityx::EntityManager& es, entityx::EventManager& events)
{
	auto gridEntity = *es.entities_with_components<Grid>().begin();
	auto gridComponent = gridEntity.component<Grid>();

	handleMoveFinishedEvent(*gridComponent);
	handleMoveEvents(events, *gridComponent);
}

void LogicSystem::handleMoveFinishedEvent(Grid& grid)
{
	if (moveFinishedEvent)
	{
		for (auto& row : grid.tiles)
		{
			for (auto& tile : row)
			{
				tile.updateView();
				tile.markMergable();
			}
		}
		spawnRandomTile(grid);
		moveAllowed = true;
	}
}

void LogicSystem::handleMoveEvents(entityx::EventManager& events, Grid& grid)
{
	for (const auto& event : moveEvents)
	{
		switch (event.code)
		{
		case sf::Keyboard::Key::Up: moveUp(events, grid); break;
		case sf::Keyboard::Key::Down: moveDown(events, grid); break;
		case sf::Keyboard::Key::Left: moveLeft(events, grid); break;
		case sf::Keyboard::Key::Right: moveRight(events, grid); break;
		}
	}
}

void LogicSystem::moveDown(entityx::EventManager& events, Grid& grid)
{
	for (int j = 0; j < GRID_DIMENSION.y; j++)
	{
		for (int i = GRID_DIMENSION.x - 1; i >= 0; i--)
		{
			auto& srcTile = grid.tiles[i][j];
			if (srcTile.getType() != TileType::BLANK)
			{
				const auto targetPosition = TilePositionFinder::findDown(i, j, srcTile, grid.tiles);
				performMove(events, srcTile, grid.tiles[targetPosition][j], Direction::Down);
			}
		}
	}
}

void LogicSystem::moveRight(entityx::EventManager& events, Grid& grid)
{
	for (int i = 0; i < GRID_DIMENSION.x; i++)
	{
		for (int j = GRID_DIMENSION.y - 1; j >= 0; j--)
		{
			auto& srcTile = grid.tiles[i][j];
			if (srcTile.getType() != TileType::BLANK)
			{
				const auto targetPosition = TilePositionFinder::findRight(j, i, srcTile, grid.tiles);
				performMove(events, srcTile, grid.tiles[i][targetPosition], Direction::Right);
			}
		}
	}
}

void LogicSystem::moveLeft(entityx::EventManager& events, Grid& grid)
{
	for (int i = 0; i < GRID_DIMENSION.x; i++)
	{
		for (int j = 1; j < GRID_DIMENSION.y; j++)
		{
			auto& srcTile = grid.tiles[i][j];
			if (srcTile.getType() != TileType::BLANK)
			{
				const auto targetPosition = TilePositionFinder::findLeft(j, i, srcTile, grid.tiles);
				performMove(events, srcTile, grid.tiles[i][targetPosition], Direction::Left);
			}
		}
	}
}

void LogicSystem::moveUp(entityx::EventManager& events, Grid& grid)
{
	for (int j = 0; j < GRID_DIMENSION.y; j++)
	{
		for (int i = 1; i < GRID_DIMENSION.x; i++)
		{
			auto& srcTile = grid.tiles[i][j];
			if (srcTile.getType() != TileType::BLANK)
			{
				const auto targetPosition = TilePositionFinder::findUp(i, j, srcTile, grid.tiles);
				performMove(events, srcTile, grid.tiles[targetPosition][j], Direction::Up);
			}
		}
	}
}

void LogicSystem::performMove(entityx::EventManager& events, Tile& srcTile, Tile& tgtTile, const Direction direction)
{
	if (&srcTile == &tgtTile)
		return;

	tgtTile.mergeWith(srcTile);
	events.emit<MoveTrigger>(srcTile, tgtTile, direction);
	srcTile.changeType(TileType::BLANK);
	srcTile.updateView();
	moveAllowed = false;
}

void LogicSystem::spawnRandomTile(Grid& grid)
{
	std::vector<sf::Vector2i> blankTiles{};
	for (int xIndex = 0; const auto & row : grid.tiles)
	{
		for (int yIndex = 0; const auto & tile : row)
		{
			if (tile.getType() == TileType::BLANK)
				blankTiles.push_back({ xIndex, yIndex });
			yIndex++;
		}
		xIndex++;
	}


	std::uniform_int_distribution<> distrib(0, static_cast<int>(blankTiles.size() - 1));
	auto randomTilePosition = distrib(generator);
	grid.tiles[blankTiles[randomTilePosition].x][blankTiles[randomTilePosition].y].changeType(TileType::VALUE_2);
	grid.tiles[blankTiles[randomTilePosition].x][blankTiles[randomTilePosition].y].updateView();
}
