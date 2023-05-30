#include "State_Turret_Hide.h"
#include "Game_Character.h"
#include "Contra_GET_ANI.h"

void State_Turret_Hide::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y, ox, oy;
	obj->GetCenterPoint(x, y);
	obj->GetSpriteOffset(StateId(), ox, oy);
	x += ox;
	y += oy;
	if (obj->IsFaceLeft())
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_HIDE_LEFT))->Render(x, y);
	else
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_HIDE_RIGHT))->Render(x, y);
}

void State_Turret_Hide::KeyPressed_Hide()
{
	_nextState = STATE_EMERGE;
}