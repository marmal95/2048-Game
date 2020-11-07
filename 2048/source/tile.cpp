#pragma once

#include "tile.hpp"

Tile::Tile()
	: shape{}, font{}, text{}, type{ TileType::BLANK }, mergeable{ true }
{
	shape.setSize(TILE_SIZE);
	font.loadFromFile("resource/ClearSans-Bold.ttf");
	text.setStyle(sf::Text::Bold);
	changeType(TileType::BLANK);
	updateView();
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
	target.draw(text);
}

void Tile::setOrigin(const sf::Vector2f& origin)
{
	Transformable::setOrigin(origin);
	shape.setOrigin(origin);
}

void Tile::setPosition(const sf::Vector2f& position)
{
	Transformable::setPosition(position);
	shape.setPosition(position);
}

void Tile::move(const sf::Vector2f& offset)
{
	Transformable::move(offset);
	shape.move(offset);
	text.move(offset);
}

void Tile::changeType(const TileType newType)
{
	type = newType;
}

void Tile::updateView()
{
	updateBackground();
	updateText();
}

void Tile::mergeWith(const Tile& source)
{
	if (getType() == TileType::BLANK)
	{
		changeType(source.getType());
	}
	else if (getType() == source.getType())
	{
		const auto tileValue = static_cast<std::underlying_type_t<TileType>>(getType()) * 2;
		changeType(TileType{ tileValue });
		markUnmergeable();
	}
}

void Tile::markUnmergeable()
{
	mergeable = false;
}

void Tile::markMergable()
{
	mergeable = true;
}

TileType Tile::getType() const
{
	return type;
}

bool Tile::isMergeable() const
{
	return mergeable;
}

void Tile::updateBackground()
{
	shape.setFillColor(TILES_COLORS.at(getType()));
}

void Tile::updateText()
{
	if (getType() != TileType::BLANK)
	{
		text.setString(std::to_string(static_cast<std::underlying_type_t<TileType>>(getType())));
		text.setFillColor(FONT_COLORS.at(getType()));
		text.setFont(font);
		text.setCharacterSize(FONT_SIZES.at(getType()));

		const auto bounds = text.getLocalBounds();
		const auto box = shape.getSize();
		text.setOrigin(getOrigin().x + ((bounds.width - box.x) / 2 + bounds.left), getOrigin().y + ((bounds.height - box.y) / 2 + bounds.top));
		text.setPosition(getPosition());
	}
	else
	{
		text.setString("");
	}
}
