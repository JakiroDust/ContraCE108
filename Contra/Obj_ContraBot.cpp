#include "Obj_ContraBot.h"
#include "Game_Platform.h"
#include "Game_Blocker.h"
#include "Contra_GET_ANI.h"
#include "State_Contra_Base.h"
#include "Game_Player.h"

Obj_ContraBot::Obj_ContraBot(int x, int y, int z) : Game_Enemy((float)x, (float)y, z, 20, 32)
{
	Obj_ContraBot((float)x, (float)y, z);
}

int Obj_ContraBot::CharID()
{
	return CHAR_CONTRA;
}

void Obj_ContraBot::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (_faceLeft)
		AddAction(DIK_LEFT);
	else
		AddAction(DIK_RIGHT);
}

void Obj_ContraBot::OnNoCollision(DWORD dt)
{
	Game_Enemy::OnNoCollision(dt);
}

void Obj_ContraBot::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_Enemy::OnCollisionWith(e);
	if (dynamic_cast<Game_Terrain*>(e->obj))
	{
		if (e->nx != 0 && e->ny == 0)
		{
			_faceLeft = !_faceLeft;
		}
		else if (e->ny < 0)
		{
			if ((footerX() -	_width / 2.0f < e->obj->x() && _faceLeft)
				|| (footerX() + _width / 2.0f > e->obj->x() + e->obj->width() && !_faceLeft))
			{
				_faceLeft = !_faceLeft;
			}
		}
	}
}

void Obj_ContraBot::GetCustomSize(int state, int& width, int& height)
{
	switch (state)
	{
	case STATE_IDLE:
		width = PLAYER_BASE_WIDTH;
		height = PLAYER_BASE_HEIGHT;
		break;
	case STATE_FALL:
		width = PLAYER_BASE_WIDTH;
		height = PLAYER_BASE_HEIGHT;
		break;
	case STATE_SWIM:
		width = PLAYER_SWIM_WIDTH;
		height = PLAYER_SWIM_HEIGHT;
		break;
	case STATE_WALK:
		width = PLAYER_BASE_WIDTH;
		height = PLAYER_BASE_HEIGHT;
		break;
	case STATE_JUMP:
		width = PLAYER_JUMP_WIDTH;
		height = PLAYER_JUMP_HEIGHT;
		break;
	case STATE_DIE:
		width = PLAYER_BASE_WIDTH;
		height = PLAYER_BASE_HEIGHT;
		break;
	default:
		break;
	}
}