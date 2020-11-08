#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include "defs.hpp"
#include "resource_holder.hpp"

enum class Font
{
    MainFont
};

class ResourcesManager
{
public:
    sf::RenderWindow window;
    ResourceHolder<sf::Font, Font> fontHolder;

    static ResourcesManager& get_instance()
    {
        static ResourcesManager instance{};
        return instance;
    }

private:
    ResourcesManager() : window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "2048 Game", sf::Style::Titlebar | sf::Style::Close), fontHolder{}
    {
        fontHolder.load(Font::MainFont, "resource/ClearSans-Bold.ttf");
    }

    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager(ResourcesManager&&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;
    ResourcesManager& operator=(ResourcesManager&&) = delete;
    ~ResourcesManager() = default;
};