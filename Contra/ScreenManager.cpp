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
}

void ScreenManager::Render()
{
	_scene->Render();
}