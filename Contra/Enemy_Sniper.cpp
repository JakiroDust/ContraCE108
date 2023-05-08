#include "Enemy_Sniper.h"
#include "Game_Player.h"
#include "Scene_Battle.h"
#include "Contra_GET_ANI.h"
#include "State_Contra_Base.h"

int Enemy_Sniper::CharID()
{
	return SNIPER;
}

void Enemy_Sniper::Execute_DieAction()
{
	Game_StationEnemy::Execute_DieAction();
	jump();
}

void Enemy_Sniper::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
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


	// idle (Sniper will look around)
	if (abs(player->x() - _x) > GAMESCREEN_WIDTH * 3 / 4)
	{
		if (_idle > 0)
		{
			if (_idle >= dt)
				_idle -= dt;
			else
				_idle = 0;
		}
		else
		{
			_idle = 120;
			if (_faceLeft)
				_lockDir = DIR_RIGHT;
			else
				_lockDir = DIR_LEFT;
		}
		return;
	}
	_idle = 0;

	// look up
	if (player->footerY() - footerY() < -_height)
	{
		if (abs(player->footerX() - footerX()) <= _width * 2)
		{
			_lockDir = DIR_TOP;
			if (floorf(player->footerX()) <= floorf(footerX()))
				AddAction(DIK_LEFT);
			else
				AddAction(DIK_RIGHT);
		}
		else if (abs(player->footerX() - footerX()) < _width * 10 && abs(player->footerY() - footerY()) > _height)
		{
			if (floorf(player->footerX()) < floorf(footerX()))
			{
				_lockDir = DIR_TOP_LEFT;
			}
			else
			{
				_lockDir = DIR_TOP_RIGHT;
			}
		}
		else
		{
			if (floorf(player->footerX()) < floorf(footerX()))
			{
				_lockDir = DIR_LEFT;
			}
			else
			{
				_lockDir = DIR_RIGHT;
			}
		}
	}
	// look down
	else if (player->y() - footerY() > 1)
	{
		if (abs(player->footerX() - footerX()) <= _width * 2 / 3.0f)
		{
			_lockDir = DIR_BOTTOM;
			if (floorf(player->footerX()) <= floorf(footerX()))
				_faceLeft = true;
			else
				_faceLeft = false;
		}
		else if (abs(player->footerX() - footerX()) < _width * 10 && abs(player->footerY() - footerY()) > _height)
		{
			if (floorf(player->footerX()) < floorf(footerX()))
			{
				_lockDir = DIR_BOTTOM_LEFT;
			}
			else
			{
				_lockDir = DIR_BOTTOM_RIGHT;
			}
		}
		else
		{
			if (floorf(player->footerX()) < floorf(footerX()))
			{
				_lockDir = DIR_LEFT;
			}
			else
			{
				_lockDir = DIR_RIGHT;
			}
		}
	}
	else
	{
		if (floorf(player->footerX()) < floorf(footerX()))
		{
			_lockDir = DIR_LEFT;
		}
		else
		{
			_lockDir = DIR_RIGHT;
		}
	}

	// shoot
	AddAction(DIK_O);
}

void Enemy_Sniper::GetCustomSize(int state, int& width, int& height)
{
	switch (state)
	{
	case STATE_IDLE:
		width = SNIPER_HIDE_WIDTH;
		height = SNIPER_HIDE_HEIGHT;
		break;
	case STATE_WALK:
		width = SNIPER_BASE_WIDTH;
		height = SNIPER_BASE_HEIGHT;
		break;
	case STATE_DIE:
		width = SNIPER_BASE_WIDTH;
		height = SNIPER_BASE_HEIGHT;
		break;
	default:
		break;
	}
}

void Enemy_Sniper::Shoot(int DIR)
{
	if (_weapon == NULL || _GunReloadInterval > 0)
		return;
	float x, y;
	GetCenterPoint(x, y);
	spawnBulletHelper::getInstance()->getSpawnCor(x, y, CharID(), DIR);

	_GunReloadInterval = _weapon->FireRate();

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();
	
	if (DIR == DIR_TOP || DIR == DIR_BOTTOM)
	{
		_weapon->Fire(x, y, DIR);
		return;
	}

	float tarX, tarY;
	player->GetCenterPoint(tarX, tarY);
	_weapon->Fire(x, y, tarX, tarY, B_SPAWN_MODE_TARGETPOS);
}