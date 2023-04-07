#include "State_Contra_Jump.h"
#include "Game_Player.h"

void State_Contra_Jump::Render()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y;
	obj->GetCenterPoint(x, y);
	if (obj->IsFaceLeft())
	{
		animations->Get(ANI_JUMP_LEFT)->Render(x, y);
	}
	else
	{
		animations->Get(ANI_JUMP_RIGHT)->Render(x, y);
	}
}

void State_Contra_Jump::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Player* obj = (Game_Player*)_srcObj;
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
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveLeft();
}

void State_Contra_Jump::KeyHold_Right()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveRight();
}
