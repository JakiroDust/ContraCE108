#include "State_Object_Hide.h"
#include "Game_Character.h"

void State_Object_Hide::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y, ox, oy;
	obj->GetCenterPoint(x, y);
	obj->GetSpriteOffset(StateId(), ox, oy);
	x += ox;
	y += oy;

	if (obj->IsFaceLeft())
		obj->_Render(Get_CharANI_ID(obj->CharID(), ACT_HIDE_LEFT), x, y);
	else
		obj->_Render(Get_CharANI_ID(obj->CharID(), ACT_HIDE_RIGHT), x, y);
}

void State_Object_Hide::KeyPressed_Active()
{
	if (_nextState == -1)
		_nextState = STATE_OBJ_EMERGE;
}