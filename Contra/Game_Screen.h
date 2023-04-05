#pragma once
#include "Game_MovableObject.h"

#define GAMESCREEN_WIDTH 320
#define GAMESCREEN_HEIGHT 240
#define WINDOW_WIDTH 336
#define WINDOW_HEIGHT 279

class Game_Screen : public Game_MovableObject
{
private:

public:
	Game_Screen(float x, float y) : Game_MovableObject(x, y, 0, GAMESCREEN_WIDTH, GAMESCREEN_HEIGHT) {}
	// Focus point will be center of screen
	void focusToPoint(float x, float y, int MapWidth, int MapHeight);
	void DeleteThis();
	void forceDie();
};

