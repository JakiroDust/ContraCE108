#include "Obj_Flame.h"
#include "Game_Platform.h"
#include "Game_Blocker.h"

int Obj_Flame::CharID()
{
	return FLAME;
}

void Obj_Flame::UpdateState()
{
	Game_SpecialObject::UpdateState();
}

void Obj_Flame::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_SpecialObject::Update(dt, coObjects);
}

void Obj_Flame::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (_moveToLeft)
	{
		if (_x > _maxRangeL)
			moveLeft();
		else
			_moveToLeft = false;
	}
	else
	{
		if (_x < _maxRangeR)
			moveRight();
		else
			_moveToLeft = true;
	}

}