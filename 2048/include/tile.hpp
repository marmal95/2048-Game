#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "defs.hpp"

class Tile : public sf::Drawable, public sf::Transformable
{
public:
	Tile();

	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	void setOrigin(const sf::Vector2f&);
	void setPosition(const sf::Vector2f&);
	void move(const sf::Vector2f&);

	void changeType(const TileType);
	void updateView();
	void mergeWith(const Tile&);
	void markUnmergeable();
	void markMergable();

	TileType getType() const;
	bool isMergeable() const;

private:
	void updateBackground();
	void updateText();

	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;
	TileType type;
	bool mergeable;
};