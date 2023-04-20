#include "State_Contra_Die.h"
#include "Game_Player.h"
#include "Contra_GET_ANI.h"

void State_Contra_Die::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y;
	obj->GetCenterPoint(x, y);
	if (obj->IsFaceLeft())
	{
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_DIE_LEFT))->Render(x, y);
	}
	else
	{
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_DIE_RIGHT))->Render(x, y);
	}
}

void State_Contra_Die::Update(DWORD dt)
{
	Game_Character* obj = (Game_Character*)_srcObj;

	if (_trigger)
	{
		obj->Execute_DieAction();
		int width, height;
		obj->GetCustomSize(StateId(), width, height);
		obj->SetHeight(height, 2);
		_trigger = false;
	}

	if (_delayDelete > 0)
	{
		_delayDelete--;
		return;
	}

	obj->DeleteThis();
}