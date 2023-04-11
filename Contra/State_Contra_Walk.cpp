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
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_LEFT))->Render(x, y);
	}
	else
	{
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_WALK_RIGHT))->Render(x, y);
	}
}

void State_Contra_Walk::Update(DWORD dt)
{
	if (_nextState != -1)
		return;
	Game_Player* obj = (Game_Player*)_srcObj;
	if (obj->height() != PLAYER_BASE_HEIGHT)
		obj->SetHeight(PLAYER_BASE_HEIGHT, 2);

	if (obj->LockFace())
		obj->SetLockFace(false);

	if (left_release && right_release)
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
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveLeft();
	left_release = false;
}

void State_Contra_Walk::KeyHold_Right()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveRight();
	right_release = false;
}

void State_Contra_Walk::KeyReleased_Left()
{
	left_release = true;
}

void State_Contra_Walk::KeyReleased_Right()
{
	right_release = true;
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