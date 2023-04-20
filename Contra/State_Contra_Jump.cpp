#include "State_Contra_Jump.h"
#include "Game_Player.h"
#include "Contra_GET_ANI.h"

void State_Contra_Jump::Render()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y;
	obj->GetCenterPoint(x, y);
	if (obj->IsFaceLeft())
	{
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_JUMP_LEFT))->Render(x, y);
	}
	else
	{
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_JUMP_RIGHT))->Render(x, y);
	}
}

void State_Contra_Jump::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Player* obj = (Game_Player*)_srcObj;
	if (obj->height() != PLAYER_JUMP_HEIGHT)
		obj->SetHeight(PLAYER_JUMP_HEIGHT, 1);

	if (obj->IsJumping())
		return;

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

void State_Contra_Jump::KeyHold_Left()
{
	State_Contra_Base::KeyHold_Left();
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveLeft();
}

void State_Contra_Jump::KeyHold_Right()
{
	State_Contra_Base::KeyHold_Right();
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveRight();
}

void State_Contra_Jump::KeyPressed_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (!obj->IsFullAutomaticGun())
	{
		if (HoldKeyDown)
		{
			if (HoldKeyLeft)
				obj->Shoot(DIR_BOTTOM_LEFT);
			else if (HoldKeyRight)
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
}

void State_Contra_Jump::KeyHold_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (obj->IsFullAutomaticGun())
	{
		if (HoldKeyDown)
		{
			if (HoldKeyLeft)
				obj->Shoot(DIR_BOTTOM_LEFT);
			else if (HoldKeyRight)
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
}