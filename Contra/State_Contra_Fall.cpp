#include "State_Contra_Fall.h"
#include "Game_Player.h"
#include "Contra_GET_ANI.h"

void State_Contra_Fall::Render()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y;
	obj->GetCenterPoint(x, y);
	if (obj->IsFaceLeft())
	{
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_FALL_LEFT))->Render(x, y);
	}
	else
	{
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_FALL_RIGHT))->Render(x, y);
	}
}

void State_Contra_Fall::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Player* obj = (Game_Player*)_srcObj;
	if (obj->IsSwimming() && _nextState == -1)
	{
		_nextState = STATE_SWIM;
		return;
	}

	if (obj->IsOnGround() && _nextState == -1)
	{
		_nextState = STATE_IDLE;
		return;
	}
}

void State_Contra_Fall::KeyHold_Left()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveLeft();
}

void State_Contra_Fall::KeyHold_Right()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveRight();
}
