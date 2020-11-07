#include "ecs_game.hpp"
#include "draw_system.hpp"
#include "logic_system.hpp"
#include "animate_system.hpp"
#include "grid.hpp"

EcsGame::EcsGame()
{
	systems.add<LogicSystem>();
	systems.add<AnimateSystem>();
	systems.add<DrawSystem>();
	systems.configure();
	entities.create().assign<Grid>();
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
