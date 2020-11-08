#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class InfoPanel : public sf::RectangleShape
{
public:
    InfoPanel();
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void setPosition(const sf::Vector2f&);

private:
    sf::Text gameTitle;
    sf::Text score;

    friend class LogicSystem;
    friend class DrawSystem;
};