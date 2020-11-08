#include "logic_system.hpp"
#include "grid.hpp"
#include "move_trigger.hpp"
#include "tile_position_finder.hpp"
#include "game_finished.hpp"

LogicSystem::LogicSystem()
    : generator{ std::random_device{}() }, moveEvents{}, moveFinishedEvent{}, initialized{}, moveAllowed{}, gameOver{}
{}

void LogicSystem::update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt)
{
    if (not initialized)
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
    initialized = true;
    auto gridEntity = *es.entities_with_components<Grid>().begin();
    auto gridComponent = gridEntity.component<Grid>();
    spawnRandomTile(*gridComponent);
    moveAllowed = true;
}

void LogicSystem::update(entityx::EntityManager& es, entityx::EventManager& events)
{
    auto gridEntity = *es.entities_with_components<Grid>().begin();
    auto gridComponent = gridEntity.component<Grid>();

    handleMoveFinishedEvent(events, *gridComponent);
    handleMoveEvents(events, *gridComponent);
}

void LogicSystem::handleMoveFinishedEvent(entityx::EventManager& events, Grid& grid)
{
    if (moveFinishedEvent)
    {
        refreshAfterMoveFinished(grid);
        spawnRandomTile(grid);

        if (!gameOver)
        {
            if (const auto gameResult = isGameOver(grid); gameResult)
                handleGameOver(events, *gameResult);
            else
                moveAllowed = true;
        }
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

void LogicSystem::refreshAfterMoveFinished(Grid& grid)
{
    for (auto& row : grid.tiles)
    {
        for (auto& tile : row)
        {
            tile.updateView();
            tile.markMergable();
        }
    }
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

std::optional<GameResult> LogicSystem::isGameOver(const Grid& grid) const
{
    bool hasMove{ false };
    for (auto rowIndex = 0; const auto & row : grid.tiles)
    {
        for (auto columnIndex = 0; const auto & tile : row)
        {
            if (tile.getType() == TileType::VALUE_2048)
            {
                return { GameResult::Won };
            }
            if (tile.getType() != TileType::BLANK)
            {
                hasMove |= TilePositionFinder::findRight(columnIndex, rowIndex, tile, grid.tiles) != columnIndex;
                hasMove |= TilePositionFinder::findLeft(columnIndex, rowIndex, tile, grid.tiles) != columnIndex;
                hasMove |= TilePositionFinder::findUp(rowIndex, columnIndex, tile, grid.tiles) != rowIndex;
                hasMove |= TilePositionFinder::findDown(rowIndex, columnIndex, tile, grid.tiles) != rowIndex;
            }

            ++columnIndex;
        }

        ++rowIndex;
    }

    return hasMove ? std::nullopt : std::make_optional(GameResult::Lost);
}

void LogicSystem::handleGameOver(entityx::EventManager& events, const GameResult result)
{
    gameOver = true;
    events.emit<GameFinished>({ result });
}
