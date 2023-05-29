#include "State_Object_Standby.h"
#include "Game_Character.h"

void State_Object_Standby::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y, ox, oy;
	obj->GetCenterPoint(x, y);
	obj->GetSpriteOffset(StateId(), ox, oy);
	x += ox;
	y += oy;

	if (obj->IsFaceLeft())
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_STANDBY_LEFT))->Render(x, y);
	else
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_STANDBY_RIGHT))->Render(x, y);
}

void State_Object_Standby::KeyPressed_Active()
{
	if (_nextState == -1)
		_nextState = STATE_OBJ_HIDE;
}