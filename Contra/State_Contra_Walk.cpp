#include "State_Contra_Walk.h"
#include "Game_Player.h"
#include "Animations.h"
#include "Contra_GET_ANI.h"

void State_Contra_Walk::Render()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y;
	obj->GetCenterPoint(x, y);
	if (obj->IsFaceLeft())
	{
		if(HoldKeyUp)
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_LEFT_LOOK_UP))->Render(x, y);
		else if(HoldKeyDown)
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_LEFT_LOOK_DOWN))->Render(x, y);
		else if(HoldKeyShoot)
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_SHOOT_WALK_LEFT))->Render(x, y);
		else
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_LEFT))->Render(x, y);
	}
	else
	{
		if (HoldKeyUp)
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_RIGHT_LOOK_UP))->Render(x, y);
		else if (HoldKeyDown)
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_RIGHT_LOOK_DOWN))->Render(x, y);
		else if (HoldKeyShoot)
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_SHOOT_WALK_RIGHT))->Render(x, y);
		else
			animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_RIGHT))->Render(x, y);
	}
}

void State_Contra_Walk::Update(DWORD dt)
{
	if (_nextState != -1)
		return;
	Game_Player* obj = (Game_Player*)_srcObj;

	int width, height;
	obj->GetCustomSize(StateId(), width, height);
	if (obj->height() != height)
	{
		obj->SetHeight(height, 2);
	}

	if (obj->LockFace())
		obj->SetLockFace(false);

	if (!HoldKeyLeft && !HoldKeyRight)
	{
		if (_nextState == -1)
		{
			_nextState = STATE_IDLE;
		}
	}

	if (_nextState != STATE_JUMP && !obj->IsOnGround())
	{
		_nextState = STATE_FALL;
	}
}

void State_Contra_Walk::KeyHold_Left()
{
	State_Contra_Base::KeyHold_Left();
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveLeft();
}

void State_Contra_Walk::KeyHold_Right()
{
	State_Contra_Base::KeyHold_Right();
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveRight();
}

int press = 0;

void State_Contra_Walk ::KeyPressed_Jump()
{
	press++;
	//
	DebugOut(L"[INFO] WALK Jump key is pressed %d\n", press);
	//
	Game_Player* obj = (Game_Player*)_srcObj;
	
	if (obj->IsJumping())
		return;

	if (_nextState == -1)
	{
		obj->jump();
		obj->SetLockFace(true);
		_nextState = STATE_JUMP;
	}
}

void State_Contra_Walk::KeyPressed_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (!obj->IsFullAutomaticGun())
	{
		if (HoldKeyDown)
		{
			if (obj->IsFaceLeft())
				obj->Shoot(DIR_BOTTOM_LEFT);
			else
				obj->Shoot(DIR_BOTTOM_RIGHT);
		}
		else if (HoldKeyUp)
		{
			if (obj->IsFaceLeft())
				obj->Shoot(DIR_TOP_LEFT);
			else
				obj->Shoot(DIR_TOP_RIGHT);
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

void State_Contra_Walk::KeyHold_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (obj->IsFullAutomaticGun())
	{
		if (HoldKeyDown)
		{
			if (obj->IsFaceLeft())
				obj->Shoot(DIR_BOTTOM_LEFT);
			else
				obj->Shoot(DIR_BOTTOM_RIGHT);
		}
		else if (HoldKeyUp)
		{
			if (obj->IsFaceLeft())
				obj->Shoot(DIR_TOP_LEFT);
			else
				obj->Shoot(DIR_TOP_RIGHT);
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