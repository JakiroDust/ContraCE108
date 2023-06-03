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
		obj->_Render(Get_CharANI_ID(obj->CharID(), ACT_STANDBY_LEFT),x,y);
	else
		obj->_Render(Get_CharANI_ID(obj->CharID(), ACT_STANDBY_RIGHT),x,y);
}

void State_Object_Standby::KeyPressed_Active()
{
	if (_nextState == -1)
		_nextState = STATE_OBJ_HIDE;
}

void State_Object_Standby::KeyPressed_Emerge()
{
	if (_nextState == -1)
		_nextState = STATE_OBJ_EMERGE;
}
