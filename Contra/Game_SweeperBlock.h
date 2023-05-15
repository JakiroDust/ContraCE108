#pragma once
#include "Game_Terrain.h"

// Any living entities touching this block will be terminated except Game_Player.
// But Player will be blocked by this object.
class Game_SweeperBlock : public Game_Terrain
{
	public:
		Game_SweeperBlock(float x, float y, int z, int width, int height) : Game_Terrain(x, y, z, width, height) {}
		bool IsBlocking() { return 1; }
};

