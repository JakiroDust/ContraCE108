#pragma once
#include "Game_MovableObject.h"

#define GAMESCREEN_WIDTH 256
#define GAMESCREEN_HEIGHT 240
#define WINDOW_WIDTH 272
#define WINDOW_HEIGHT 279

class Game_Screen : public Game_MovableObject
{
	private:
		int _ViewBoxWidth = 1;
		int _ViewBoxHeight = 1;
	public:
		Game_Screen(float x, float y) : Game_MovableObject(x, y, 0, GAMESCREEN_WIDTH, GAMESCREEN_HEIGHT) { _gravity = false; }
		// Focus point will be center of screen
		void focusToPoint(float x, float y, int MapWidth, int MapHeight);
		void focusToPoint(float x, float y) { focusToPoint(x, y, _ViewBoxWidth, _ViewBoxHeight); }
		void SetViewBox(int width, int height) { _ViewBoxWidth = width; _ViewBoxHeight = height; }
		int ViewBoxWidth() { return _ViewBoxWidth; }
		int ViewBoxHeight() { return _ViewBoxHeight; }
		void DeleteThis();
		void forceDie();
};

