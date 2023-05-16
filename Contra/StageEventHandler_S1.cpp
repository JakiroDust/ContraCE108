#include "StageEventHandler_S1.h"
#include "Scene_Battle.h"
#include "ScreenManager.h"
#include "Enemy_Infary.h"

void StageEventHandler_S1::Update(DWORD dt)
{
	// Make Camera focus to player
	Set_Camera_Focus_Player();

	// Execute event base on camera position
	Game_Screen* screen = ScreenManager::GetInstance()->Screen();
	float cx, cy;
	screen->GetCenterPoint(cx, cy);

	if (cx >= 224 && cx <= 544)
	{
		Spawn_Infary(dt, cx, 160);
	}	

}

void StageEventHandler_S1::Load()
{
	_srcScene->Create_Stage_Demo();

	_srcScene->p1()->ChangeWeapon(new Equip_Gun_S());
	return;

	// PROTYPE
	SoundSystem* SS = SoundSystem::getInstance();
	SS->playBGM(BGM_JUNGLE);
	_srcScene->_ParseSection_DICT("textures\\MAP1");
	// ParseSection_OBJECT
	// ParseSection_animation

	// Add sweeper block
	_sweeper.reset(new Game_SweeperBlock(-100, 0, 0, 100, GAMESCREEN_HEIGHT));
	_srcScene->add_object(move(_sweeper));
}

// ===================================================================
// EVENTS

void StageEventHandler_S1::Spawn_Infary(DWORD dt, float camX, float spawnPosY)
{
	if (spawn_infary_ticker >= dt)
	{
		spawn_infary_ticker -= dt;
		return;
	}
	spawn_infary_ticker = SPAWN_INFARY_INTERVAL;

	for (int i = 0; i < 1; i++)
	{
		unique_ptr <Enemy_Infary> redgunner(new Enemy_Infary(camX + GAMESCREEN_WIDTH/2 + 32, spawnPosY, 2));
		_srcScene->add_object(move(redgunner));
	}
}