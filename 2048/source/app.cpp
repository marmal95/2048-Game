#include "app.hpp"
#include "resource_manager.hpp"
#include "ecs_game.hpp"


void App::run()
{
	auto& window = ResourcesManager::get_instance().window;

	EcsGame game{};
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event{};

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased)
				game.handleKeyEvent(event.key);
		}

		window.clear(BACKGROUND_COLOR);
		game.update(clock.restart().asSeconds());
		window.display();
	}
}