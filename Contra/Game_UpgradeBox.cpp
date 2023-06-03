#include "Game_UpgradeBox.h"
#include <math.h>
#include "Scene_Battle.h"
#include "ScreenManager.h"

namespace UPGRADE
{
#define BoxFlying_Radius 20
#define BoxFlying_Speed 0.25f
#define PI 3.14
#define BoxFlying_ExpireTime 5000
}
using namespace UPGRADE;
Game_UpgradeBoxFlying::Game_UpgradeBoxFlying(float _x, float _y, int _type): Game_UpgradeBoxBase(_x,_y,2,24,15,_type)
{
	_hp = 1;
	start_x = _x;
	start_y = _y;
	start_dt = 0;
	_SpriteId = 958890;
}


void Game_UpgradeBoxFlying::Update(DWORD dt)
{
	start_dt += dt;
	if (start_dt >= BoxFlying_ExpireTime)
		_isDeleted = true;
	float x = (int)start_dt * BoxFlying_Speed/PI;
	float y = sin(x * PI / BoxFlying_Radius/2) * BoxFlying_Radius*2;
	_x = start_x+ x;
	_y = start_y+ y;
}

void Game_UpgradeBoxFlying::Render()
{
	_Render(_SpriteId);
}


Game_UpgradeBoxStation::Game_UpgradeBoxStation(float _x, float _y, int _type) : Game_UpgradeBoxBase(_x, _y, 2, 31, 31, _type)
{
	_hp = 5;
	_haveStandby = true;
}
void Game_UpgradeBoxStation::Render()
{
	RenderHitbox();
	if (_state.get() != NULL)
		_state->Render();
}

void Game_UpgradeBoxStation::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();

	if (_ActionQueue.size() > 0)
		return;

	if (_needRender == false)
		return;

	if (_state->StateId() == 20)
	{
		// in active range
		if (abs(player->x() - _x) <= TURRET_TRIGGER_RANGE_X
			&& abs(player->y() - _y) <= TURRET_TRIGGER_RANGE_Y)
		{
			AddAction(DIK_E);
			return;
		}
		return;
	}
}