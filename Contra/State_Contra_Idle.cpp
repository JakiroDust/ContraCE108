#include "State_Contra_Idle.h"
#include "Game_Player.h"
#include "Animations.h"

void State_Contra_Idle::Render()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y;
	obj->GetCenterPoint(x, y);
	if (obj->IsFaceLeft())
	{
		animations->Get(ANI_IDLE_LEFT)->Render(x, y);
	}
	else
	{
		animations->Get(ANI_IDLE_RIGHT)->Render(x, y);
	}
}

void State_Contra_Idle::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Player* obj = (Game_Player*)_srcObj;
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
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveLeft();
	if (_nextState == -1)
		_nextState = STATE_WALK;
}

void State_Contra_Idle::KeyHold_Right()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveRight();
	if (_nextState == -1)
		_nextState = STATE_WALK;
}

void State_Contra_Idle::KeyPressed_Jump()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->jump();
	if (_nextState == -1)
	{
		obj->SetLockFace(true);
		_nextState = STATE_JUMP;
	}

}