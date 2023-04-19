#include "Obj_ContraBot.h"
#include "Game_Platform.h"
#include "Game_Blocker.h"
#include "Contra_GET_ANI.h"

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
			if ((footerX() - _width / 2 < e->obj->x() && _faceLeft)
				|| (footerX() + _width / 2 > e->obj->x() + e->obj->width() && !_faceLeft))
			{
				_faceLeft = !_faceLeft;
			}
		}
	}
}