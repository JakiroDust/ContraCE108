#include "Enemy_Turret.h"
#include "Scene_Battle.h"
#include "Contra_GET_ANI.h"
#include "State_Contra_Base.h"

int Enemy_Turret::CharID()
{
	return TURRET;
}

void Enemy_Turret::Execute_DieAction()
{
	Game_StationEnemy::Execute_DieAction();
	jump();
}

void Enemy_Turret::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();

	if (_ActionQueue.size() > 0)
		return;

	switch (_lockDir)
	{
	case DIR_LEFT:
		AddAction(DIK_NUMPAD4);
		break;
	case DIR_RIGHT:
		AddAction(DIK_NUMPAD6);
		break;
	case DIR_BOTTOM:
		AddAction(DIK_NUMPAD2);
		break;
	case DIR_TOP:
		AddAction(DIK_NUMPAD8);
		break;
	case DIR_BOTTOM_LEFT:
		AddAction(DIK_NUMPAD1);
		break;
	case DIR_BOTTOM_RIGHT:
		AddAction(DIK_NUMPAD3);
		break;
	case DIR_TOP_LEFT:
		AddAction(DIK_NUMPAD7);
		break;
	case DIR_TOP_RIGHT:
		AddAction(DIK_NUMPAD9);
		break;
	default:
		break;
	}

	if (_needRender == false)
		return;

	if (_GunReloadInterval > 0)
		return;

	// already locked target, perform shoot
	if (_state->StateId() == STATE_WALK && _ActionQueue.size() > 0)
		AddAction(DIK_O);

	// active range
	if (abs(player->x() - _x) > GAMESCREEN_WIDTH * TURRET_TRIGGER_RANGE_X
		&& abs(player->y() - _y) > GAMESCREEN_HEIGHT * TURRET_TRIGGER_RANGE_Y)
	{
		// No active. Perform hiding
		if (_state->StateId() != STATE_IDLE)
		AddAction(DIK_P);
		return;
	}

	// lock target
	float pcx, pcy, cx, cy;
	player->GetCenterPoint(pcx, pcy);
	GetCenterPoint(cx, cy);
	_lockDir = Detect_Dir(cx, cy, pcx, pcy);
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