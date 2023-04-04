#pragma once

#include "Scene_Base.h"
#include "ScreenManager.h"
#include <string>
#include "debug.h"
#include "Game_Player.h"
#include "Game_Layer.h"
#include "Game_Blocker.h"
#include "Game_Terrain.h"
#include "Game_Collision.h"

using namespace std;


class Scene_Battle : public Scene_Base
{
	private: 
		Game_Player* _p1 = NULL;
		Game_Player* _p2 = NULL;
		vector<Game_Layer*>* _layers = NULL;
		vector<Game_ObjectBase*>* _objects = NULL;
		int _mapWidth = 1;
		int _mapHeight = 1;

	public:
		~Scene_Battle();
		vector<Game_ObjectBase*>* objects() { return _objects; }
		Game_Player* p1() { return _p1; }
		Game_Player* p2() { return _p2; }
		void SetMapSize(int width, int height) { _mapWidth = width; _mapHeight = height; }

		void Render();
		void Update(DWORD dt);
};

