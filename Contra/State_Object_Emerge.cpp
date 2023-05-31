#include "State_Object_Emerge.h"
#include "Game_Character.h"

void State_Object_Emerge::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y, ox, oy;
	obj->GetCenterPoint(x, y);
	obj->GetSpriteOffset(StateId(), ox, oy);
	x += ox;
	y += oy;

	if (obj->IsFaceLeft())
		obj->_Render(Get_CharANI_ID(obj->CharID(), ACT_EMERGE_LEFT),x,y);
	else
		obj->_Render(Get_CharANI_ID(obj->CharID(), ACT_EMERGE_RIGHT),x,y);
}