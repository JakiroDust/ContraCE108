#include "ScreenManager.h"

ScreenManager* ScreenManager::__instance = NULL;

ScreenManager* ScreenManager::GetInstance()
{
	if (__instance == NULL) __instance = new ScreenManager();
	return __instance;
}

ScreenManager::ScreenManager()
{
	_screen = new Game_Screen(0, 0);
}



void ScreenManager::Update(DWORD dt)
{
	_scene->Update(dt);
	// Camera Update
	if (dynamic_cast<Scene_Battle*>(_scene))
		_screen->Update(dt, ((Scene_Battle*)_scene)->objects());
}

void ScreenManager::Render()
{
	_scene->Render();
}

void ScreenManager::Load(LPCWSTR gameFile)
{
	// Build later

	// Test
	Create_Scene_Demo();
}

// DEMO

void ScreenManager::Create_Scene_Demo()
{
	Scene_Battle* scene = new Scene_Battle();
	scene->Create_Stage_Demo();
	_scene = scene;
	
}