#include "draw_system.hpp"
#include "grid.hpp"
#include "resource_manager.hpp"
#include "animated.hpp"

DrawSystem::DrawSystem()
    : gameFinishedEvent{}, font{}, text{}
{
    font.loadFromFile("resource/ClearSans-Bold.ttf");
    text.setFont(font);
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize(64);
    text.setFillColor(FONT_COLORS.at(TileType::VALUE_2));
}

void DrawSystem::update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt)
{
    auto& window = ResourcesManager::get_instance().window;
    es.each<Grid>([&](entityx::Entity entity, Grid& grid) {
        window.draw(grid.grid);
        for (const auto& gridRow : grid.tiles)
            for (const auto& tile : gridRow)
                window.draw(tile);
        });

    es.each<Animated>([&](entityx::Entity entity, Animated& animated) {
        window.draw(animated.animatedTile);
        });

    if (gameFinishedEvent)
    {
        window.draw(text);
    }
}

void DrawSystem::configure(entityx::EventManager& events)
{
    events.subscribe<GameFinished>(*this);
}

void DrawSystem::receive(const GameFinished& event)
{
    gameFinishedEvent = event;
    handleGameOver();
}

void DrawSystem::handleGameOver()
{
    if (gameFinishedEvent->result == GameResult::Won)
        text.setString("You won!");
    else
        text.setString("You lost!");

    const auto textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    text.setPosition(sf::Vector2f(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2));
}
