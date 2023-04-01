#pragma once
using namespace std;

#include "Game_Player.h"
#include "Game_Terrain.h"
#include "BattleManager.h"
#include <vector>

class ScreenManager
{
	private:
		static vector<Game_ObjectBase*> _drawCollection;

		//static Game_Scene _scene;
	public:
		static void draw();

		// get a list of Game_Objects that need to draw in this frame.
		static void get_DrawCollection();
};

