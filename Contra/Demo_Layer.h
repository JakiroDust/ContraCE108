#pragma once
#include "Game_Layer.h"
class Demo_Layer : public Game_Layer
{
public:
	Demo_Layer(float x, float y, int z, int width, int height) : Game_Layer(x, y, z, width, height) { _SpriteId = 100; }
};

