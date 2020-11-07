#pragma once

enum class GameResult
{
	Won, Lost
};

struct GameFinished
{
	GameResult result;
};