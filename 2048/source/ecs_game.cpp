#include "ecs_game.hpp"
#include "draw_system.hpp"
#include "logic_system.hpp"
#include "animate_system.hpp"
#include "grid.hpp"
#include "info_panel.hpp"

EcsGame::EcsGame()
{
    systems.add<LogicSystem>();
    systems.add<AnimateSystem>();
    systems.add<DrawSystem>();
    systems.configure();

    auto infoPanelEntity = entities.create().assign<InfoPanel>();
    auto gridEntity = entities.create().assign<Grid>();

    auto& infoPanel = *infoPanelEntity;
    infoPanel.setSize({ GRID_SIZE.x, TILE_SIZE.y });
    infoPanel.setPosition({ 50, 0 });

    auto& grid = *gridEntity;
    grid.setPosition({ 50, infoPanel.getPosition().y + infoPanel.getSize().y });
}

void EcsGame::update(const entityx::TimeDelta dt)
{
    systems.update<LogicSystem>(dt);
    systems.update<AnimateSystem>(dt);
    systems.update<DrawSystem>(dt);
}

void EcsGame::handleKeyEvent(const sf::Event::KeyEvent& event)
{
    events.emit<sf::Event::KeyEvent>(event);
}
