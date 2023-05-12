#include "Game_Screen.h"

void Game_Screen::focusToPoint(float x, float y, int MapWidth = 1, int MapHeight = 1)
{
	// Fix position on map
	if (MapWidth <= _width)
	{
		x = MapWidth / 2.0f - 1;
	}
	if (MapHeight <= _height)
	{
		y = MapHeight / 2.0f - 1;
	}
	if (x - _width / 2.0f < 0)
	{
		x = _width / 2.0f - 1;
	}
	if (x + _width / 2.0f > MapWidth)
	{
		x = MapWidth + 1 - _width / 2.0f;
	}
	if (y - _height / 2.0f < 0)
	{
		y = _height / 2.0f;
	}
	if (y + _height / 2.0f > MapHeight)
	{
		y = MapHeight + 1 - _height / 2.0f;
	}

	// Set CAM position
	x = (FLOAT)floor(x);
	y = (FLOAT)ceilf(y);
	_x = x - _width / 2.0f;
	_y = y + _height / 2.0f;

	// Update later
}

void Game_Screen::DeleteThis()
{
	DebugOut(L"[INFO] This object can't be deleted\n");
}

void Game_Screen::forceDie()
{
	DebugOut(L"[INFO] This object can't be killed\n");
}