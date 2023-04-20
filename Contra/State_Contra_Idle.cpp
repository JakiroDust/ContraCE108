#include "State_Contra_Idle.h"
#include "Game_Player.h"
#include "Animations.h"
#include "Contra_GET_ANI.h"

void State_Contra_Idle::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y;
	obj->GetCenterPoint(x, y);
	if (obj->IsFaceLeft())
	{
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_IDLE_LEFT))->Render(x, y);
	}
	else
	{
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_IDLE_RIGHT))->Render(x, y);
	}
}

void State_Contra_Idle::Update(DWORD dt)
{
	if (_nextState != -1)
		return;
	
	Game_Character* obj = (Game_Character*)_srcObj;
	if (obj->height() != PLAYER_BASE_HEIGHT)
		obj->SetHeight(PLAYER_BASE_HEIGHT, 2);

	if (obj->LockFace())
		obj->SetLockFace(false);

	if (!obj->IsOnGround())
	{
		_nextState = STATE_FALL;
		return;
	}
}

void State_Contra_Idle::KeyHold_Left()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveLeft();
	if (_nextState == -1)
		_nextState = STATE_WALK;
}

void State_Contra_Idle::KeyHold_Right()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	obj->moveRight();
	if (_nextState == -1)
		_nextState = STATE_WALK;
}

//void State_Contra_Idle::KeyHold_Down()
//{
//	HoldKeyDown = true;
//}
//
//void State_Contra_Idle::KeyReleased_Down()
//{
//	HoldKeyDown = false;
//}

void State_Contra_Idle::KeyPressed_Jump()
{
	//
	DebugOut(L"[INFO] IDLE Jump key is pressed\n");
	//
	Game_Character* obj = (Game_Character*)_srcObj;
	if (obj->IsJumping())
		return;

	if (HoldKeyDown)
	{
		obj->SetJumpDown(true);
		return;
	}

	if (_nextState == -1)
	{
		obj->jump();
		obj->SetLockFace(true);
		_nextState = STATE_JUMP;
	}

}

void State_Contra_Idle::KeyPressed_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (!obj->IsFullAutomaticGun())
	{
		if (obj->IsFaceLeft())
			obj->Shoot(DIR_LEFT);
		else
			obj->Shoot(DIR_RIGHT);
	}
}

void State_Contra_Idle::KeyHold_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	if (obj->IsFullAutomaticGun())
	{
		if (obj->IsFaceLeft())
			obj->Shoot(DIR_LEFT);
		else
			obj->Shoot(DIR_RIGHT);
	}
}