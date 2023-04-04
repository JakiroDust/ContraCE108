#pragma once
#include <vector>

using namespace std;

//#include "Game_Player.h"
//#include "Game_Terrain.h"
//#include "BattleManager.h"
#include "Game_Screen.h"
#include "Scene_Battle.h"


class ScreenManager
{
private:
	static ScreenManager* __instance;
	vector<Game_ObjectBase*> _drawCollection;
	Game_Screen* _screen = NULL;
	Scene_Base* _scene = NULL;

public:
	static ScreenManager* GetInstance();
	ScreenManager();
	Game_Screen* Screen() { return _screen; }
	Scene_Base* Scene() { return _scene; }
	void Render();
	void Update(DWORD dt);
};

