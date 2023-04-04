#pragma once
#include "Game_Terrain.h"

class Game_Blocker : public Game_Terrain
{
	public:
		bool IsBlocking() { return 1; }
};

