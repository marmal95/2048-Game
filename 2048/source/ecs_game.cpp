#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "constants.hpp"

class ResourcesManager
{
public:
	sf::RenderWindow window;

	static ResourcesManager* get_instance()
	{
		if (!instance)
			instance = new ResourcesManager();
		return instance;
	}

	static ResourcesManager& get_instance_ref()
	{
		return *get_instance();
	}

	static void delete_instance()
	{
		delete instance;
	}

private:
	ResourcesManager() : window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "2048 Game", sf::Style::Titlebar | sf::Style::Close) {}
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;
	ResourcesManager(ResourcesManager&&) = delete;
	ResourcesManager& operator=(ResourcesManager&&) = delete;
	~ResourcesManager() = default;

	static inline ResourcesManager* instance = nullptr;
};