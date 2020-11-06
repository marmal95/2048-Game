#pragma once

#include <entityx/entityx.h>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

class EcsGame : public entityx::EntityX
{
public:
	EcsGame();
	void update(const entityx::TimeDelta);
	void handleKeyEvent(const sf::Event::KeyEvent&);
};