#pragma once

#include <entityx/entityx.h>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <optional>
#include <random>
#include "move_finished.hpp"
#include "game_finished.hpp"
#include "defs.hpp"

class Grid;
class Tile;
class InfoPanel;

class LogicSystem : public entityx::System<LogicSystem>, public entityx::Receiver<LogicSystem>
{
public:
    LogicSystem();
    void update(entityx::EntityManager&, entityx::EventManager&, entityx::TimeDelta);
    void configure(entityx::EventManager&) override;
    void receive(const sf::Event::KeyEvent&);
    void receive(const MoveFinished&);

private:
    void initialize(entityx::EntityManager&);
    void update(entityx::EntityManager&, entityx::EventManager&);
    void handleMoveFinishedEvent(entityx::EventManager&, Grid&, InfoPanel&);
    void handleMoveEvents(entityx::EventManager&, Grid&);

    void moveDown(entityx::EventManager&, Grid&);
    void moveRight(entityx::EventManager&, Grid&);
    void moveLeft(entityx::EventManager&, Grid&);
    void moveUp(entityx::EventManager&, Grid&);
    void performMove(entityx::EventManager&, Tile&, Tile&, const Direction);

    void refreshAfterMoveFinished(Grid&, InfoPanel&);
    void spawnRandomTile(Grid&);
    std::optional<GameResult> isGameOver(const Grid&) const;
    void handleGameOver(entityx::EventManager&, const GameResult);

    std::mt19937 generator;
    std::vector<sf::Event::KeyEvent> moveEvents;
    std::optional<MoveFinished> moveFinishedEvent;
    uint32_t score;
    bool initialized;
    bool moveAllowed;
    bool gameOver;
};