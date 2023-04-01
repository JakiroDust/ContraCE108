#pragma once

#include "Game_Player.h"
#include "Game_Terrain.h"

using namespace std;

#include <vector>

class BattleManager
{
	public:
		static Game_Player* p1;
		static Game_Player* p2;
		
		static vector<Game_Terrain> *terrains;
};

