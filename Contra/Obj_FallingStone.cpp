#include "Obj_FallingStone.h"
#include "Game_Platform.h"

int Obj_FallingStone::CharID()
{
	return FALLING_STONE;
}

void Obj_FallingStone::UpdateState()
{
	Game_SpecialObject::UpdateState();
}

void Obj_FallingStone::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (_ForceY == 0 && _finishEmerge)
		_vy = STONE_FALLING_SPEED;
	Game_SpecialObject::Update(dt, coObjects);
}

void Obj_FallingStone::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_SpecialObject::OnCollisionWith(e);
	if (dynamic_cast<Game_Platform*>(e->obj))
	{
		bool check = true;
		for (int i = 0; i < _touchList.size(); i++)
		{
			if (_touchList[i] == e->obj->id())
			{
				check = false;
			}
		}
		if (check)
		{
			_touchList.push_back(e->obj->id());
			_ForceY += STONE_BOUNCE_HEIGHT;
			return;
		}
	}
}

void Obj_FallingStone::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (_ForceX != 0 || _ForceY != 0 || _finishEmerge == false)
		return;
	//-------------------------------------------------
	// shake effect
	if (_EmergeTick > dt)
	{
		_EmergeTick -= dt;
		// shake
		if (_faceLeft)
			_ForceX = -STONE_SHAKE_RANGE * 2;
		else
			_ForceX = STONE_SHAKE_RANGE * 2;
	}
	else
	{
		_finishEmerge = true;
		_EmergeTick = 0;
		SetPosition(_baseX, _y);
		_gravity = true;
		_BodyDamage = true;
		AddAction(DIK_O);
	}
}