#include "State_Station.h"
#include "Game_Enemy.h"
#include "Contra_GET_ANI.h"

void State_Station::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y;
	obj->GetCenterPoint(x, y);
	if (HoldKeyLeft)
	{
		if (HoldKeyUp)
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_LEFT_LOOK_UP))->Render(x, y);
		else if (HoldKeyDown)
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_LEFT_LOOK_DOWN))->Render(x, y);
		else
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_LEFT))->Render(x, y);
	}
	else if (HoldKeyRight)
	{
		if (HoldKeyUp)
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_RIGHT_LOOK_UP))->Render(x, y);
		else if (HoldKeyDown)
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_RIGHT_LOOK_DOWN))->Render(x, y);
		else
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_RIGHT))->Render(x, y);
	}
	else if (HoldKeyDown)
	{
		if (obj->IsFaceLeft())
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_LOOK_DOWN_LEFT))->Render(x, y);
		else
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_LOOK_DOWN_RIGHT))->Render(x, y);
	}
	else if (HoldKeyUp)
	{
		if (obj->IsFaceLeft())
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_LOOK_UP_LEFT))->Render(x, y);
		else
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_LOOK_UP_RIGHT))->Render(x, y);
	}
	else 
	{
		if (obj->IsFaceLeft())
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_LEFT))->Render(x, y);
		else
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_RIGHT))->Render(x, y);
	}
}

void State_Station::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Character* obj = (Game_Character*)_srcObj;

	// do something
}

void State_Station::KeyPressed_Left()
{
	State_Contra_Base::KeyHold_Left();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveLeft();
}

void State_Station::KeyPressed_Right()
{
	State_Contra_Base::KeyHold_Right();
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveRight();
}

void State_Station::KeyPressed_Jump()
{
	_nextState = STATE_IDLE;
}

void State_Station::KeyPressed_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;

	if (HoldKeyDown)
	{
		if (obj->IsFaceLeft())
			obj->Shoot(DIR_BOTTOM_LEFT);
		else if (obj->IsFaceLeft())
			obj->Shoot(DIR_BOTTOM_RIGHT);
		else
			obj->Shoot(DIR_BOTTOM);
	}
	else if (HoldKeyUp)
	{
		if (HoldKeyLeft)
			obj->Shoot(DIR_TOP_LEFT);
		else if (HoldKeyRight)
			obj->Shoot(DIR_TOP_RIGHT);
		else
			obj->Shoot(DIR_TOP);
	}
	else
	{
		if (obj->IsFaceLeft())
			obj->Shoot(DIR_LEFT);
		else
			obj->Shoot(DIR_RIGHT);
	}

}