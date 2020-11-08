#include "draw_system.hpp"
#include "grid.hpp"
#include "resource_manager.hpp"
#include "animated.hpp"
#include "info_panel.hpp"

DrawSystem::DrawSystem()
    : gameFinishedEvent{}, text{}
{
    text.setFont(ResourcesManager::get_instance().fontHolder.getResource(Font::MainFont));
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize(64);
    text.setFillColor(FONT_COLORS.at(TileType::VALUE_2));
}

void DrawSystem::update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt)
{
    auto& window = ResourcesManager::get_instance().window;

    auto infoPanelEntity = *es.entities_with_components<InfoPanel>().begin();
    auto& infoPanelComponent = *infoPanelEntity.component<InfoPanel>();
    window.draw(infoPanelComponent);

    auto gridEntity = *es.entities_with_components<Grid>().begin();
    auto& gridComponent = *gridEntity.component<Grid>();

    window.draw(gridComponent.grid);
    for (const auto& gridRow : gridComponent.tiles)
        for (const auto& tile : gridRow)
            window.draw(tile);
        
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
