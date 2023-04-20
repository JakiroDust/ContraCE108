#include "State_Contra_Swim.h"
#include "Game_Player.h"
#include "Contra_GET_ANI.h"

void State_Contra_Swim::Render()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y;
	obj->GetCenterPoint(x, y);
	if (obj->IsFaceLeft())
	{
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_SWIM_LEFT))->Render(x, y);
	}
	else
	{
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_SWIM_RIGHT))->Render(x, y);
	}
}

void State_Contra_Swim::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Player* obj = (Game_Player*)_srcObj;

	if (obj->height() != PLAYER_SWIM_HEIGHT)
		obj->SetHeight(PLAYER_SWIM_HEIGHT, 2);
	
	if (!obj->IsSwimming())
	{
		if (_nextState == -1)
		{
			_nextState = STATE_IDLE;
		}
	}
}

void State_Contra_Swim::KeyHold_Left()
{
	State_Contra_Base::KeyHold_Left();
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveLeft();
}

void State_Contra_Swim::KeyHold_Right()
{
	State_Contra_Base::KeyHold_Right();
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveRight();
}

void State_Contra_Swim::KeyPressed_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (!obj->IsFullAutomaticGun())
	{
		if (HoldKeyDown)
		{
			// do nothing
			return;
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
}

void State_Contra_Swim::KeyHold_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (obj->IsFullAutomaticGun())
	{
		if (HoldKeyDown)
		{
			// do nothing
			return;
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
}
