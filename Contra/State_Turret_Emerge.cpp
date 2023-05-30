#include "State_Turret_Emerge.h"
#include "Game_Character.h"
#include "Contra_GET_ANI.h"

void State_Turret_Emerge::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y, ox, oy;
	obj->GetCenterPoint(x, y);
	obj->GetSpriteOffset(StateId(), ox, oy);
	x += ox;
	y += oy;
	if (obj->IsFaceLeft())
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_EMERGE_LEFT))->Render(x, y);
	else 
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_EMERGE_RIGHT))->Render(x, y);
}

void State_Turret_Emerge::Update(DWORD dt)
{
	if (_nextState != -1)
		return;
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani = NULL;
	if (obj->IsFaceLeft())
		ani = animations->Get(Get_CharANI_ID(obj->CharID(), ACT_EMERGE_LEFT));
	else
		ani = animations->Get(Get_CharANI_ID(obj->CharID(), ACT_EMERGE_RIGHT));
	if (ani->checkFinalFrame())
	{
		if (waitForChange > dt)
		{
			waitForChange -= dt;
		}
		else
		{
			_nextState = STATE_ACTIVE;
		}
	}
}