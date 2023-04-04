#pragma once
#include "Game_Terrain.h"

class Game_Platform : public Game_Terrain
{
	public:
		bool IsBlocking() { return 0; }
};

