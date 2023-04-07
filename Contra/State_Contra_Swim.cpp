#include "State_Contra_Swim.h"
#include "Game_Player.h"

void State_Contra_Swim::Render()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y;
	obj->GetCenterPoint(x, y);
	if (obj->IsFaceLeft())
	{
		animations->Get(ANI_SWIM_LEFT)->Render(x, y);
	}
	else
	{
		animations->Get(ANI_SWIM_RIGHT)->Render(x, y);
	}
}

void State_Contra_Swim::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Player* obj = (Game_Player*)_srcObj;

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
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveLeft();
}

void State_Contra_Swim::KeyHold_Right()
{
	Game_Player* obj = (Game_Player*)_srcObj;
	obj->moveRight();
}

void State_Contra_Swim::KeyHold_Down()
{

}

void State_Contra_Swim::KeyHold_Up()
{

}