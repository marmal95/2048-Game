#include "info_panel.hpp"
#include "resource_manager.hpp"
#include "defs.hpp"
#include <string>

InfoPanel::InfoPanel()
{
    const auto& font = ResourcesManager::get_instance().fontHolder.getResource(Font::MainFont);
    const auto& color = FONT_COLORS.at(TileType::VALUE_2);

    gameTitle.setString("2048");
    gameTitle.setCharacterSize(FONT_SIZES.at(TileType::VALUE_2));
    gameTitle.setFont(font);
    gameTitle.setFillColor(color);

    score.setString("Score: 0");
    score.setCharacterSize(FONT_SIZES.at(TileType::VALUE_1024));
    score.setFont(font);
    score.setFillColor(color);
}

void InfoPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(gameTitle);
    target.draw(score);
}

void InfoPanel::setPosition(const sf::Vector2f& position)
{
    Transformable::setPosition(position);
    const auto box = getSize();

    auto bounds = gameTitle.getLocalBounds();
    gameTitle.setOrigin(0, getOrigin().y + ((bounds.height - box.y) / 2 + bounds.top));
    gameTitle.setPosition({ 50, position.y });

    bounds = score.getLocalBounds();
    score.setOrigin(0, getOrigin().y + ((bounds.height - box.y) / 2 + bounds.top));
    score.setPosition({ 50 + getSize().x / 2, position.y });
}