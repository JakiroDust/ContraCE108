#include "Enemy_Turret.h"
#include "Scene_Battle.h"
#include "Contra_GET_ANI.h"
#include "State_Contra_Base.h"
#include "State_Turret_Active.h"

int Enemy_Turret::CharID()
{
	return TURRET;
}

void Enemy_Turret::Execute_DieAction()
{
	Game_StationEnemy::Execute_DieAction();
}

void Enemy_Turret::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();

	if (_ActionQueue.size() > 0)
		return;

	if (_needRender == false)
		return;

	// active range
	if (abs(player->x() - _x) > TURRET_TRIGGER_RANGE_X
		&& abs(player->y() - _y) > TURRET_TRIGGER_RANGE_Y)
	{
		// No active. Perform hiding
		if (_state->StateId() != STATE_IDLE)
			AddAction(DIK_P);
		return;
	}

	if (_rotate_CD > dt)
	{
		_rotate_CD -= dt;
	}
	else
	{
		_rotate_CD = TURRET_ROTATE_CD - (dt - _rotate_CD);
		if (_state->StateId() == STATE_ACTIVE)
		{
			State_Turret_Active* state = (State_Turret_Active*)(_state.get());
			if (_lockDir < state->CurrentAngle())
				AddAction(DIK_RIGHT);
			else if (_lockDir > state->CurrentAngle())
				AddAction(DIK_LEFT);
		}
	}

	if (_GunReloadInterval > 0)
		return;

	// already locked target, perform shoot
	if (_state->StateId() == STATE_WALK && _ActionQueue.size() > 0)
		AddAction(DIK_O);

	// lock target
	float pcx, pcy, cx, cy;
	player->GetCenterPoint(pcx, pcy);
	GetCenterPoint(cx, cy);
	_lockDir = Detect_Dir12(cx, cy, pcx, pcy);
}

void Enemy_Turret::GetCustomSize(int state, int& width, int& height)
{
	width = TURRET_BASE_WIDTH;
	height = TURRET_BASE_HEIGHT;
}

void Enemy_Turret::Shoot(int DIR)
{
	if (_weapon == NULL || _GunReloadInterval > 0)
		return;
	float x, y;
	GetCenterPoint(x, y);
	spawnBulletHelper::getInstance()->getSpawnCor(x, y, CharID(), DIR);

	_GunReloadInterval = _weapon->FireRate();

	_weapon->Fire(x, y, DIR);
	return;
}