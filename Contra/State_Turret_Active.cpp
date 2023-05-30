#include "State_Turret_Active.h"
#include "Game_Character.h"

void State_Turret_Active::Render()
{
	Game_Character* obj = (Game_Character*)_srcObj;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y, ox, oy;
	obj->GetCenterPoint(x, y);
	obj->GetSpriteOffset(StateId(), ox, oy);
	x += ox;
	y += oy;
	switch (_currentAngle)
	{
	case DIR_1_OCLOCK:
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_ANGLE_1_OCLOCK))->Render(x, y);
		break;
	case DIR_2_OCLOCK:
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_ANGLE_2_OCLOCK))->Render(x, y);
		break;
	case DIR_3_OCLOCK:
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_ANGLE_3_OCLOCK))->Render(x, y);
		break;
	case DIR_4_OCLOCK:
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_ANGLE_4_OCLOCK))->Render(x, y);
		break;
	case DIR_5_OCLOCK:
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_ANGLE_5_OCLOCK))->Render(x, y);
		break;
	case DIR_6_OCLOCK:
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_ANGLE_6_OCLOCK))->Render(x, y);
		break;
	case DIR_7_OCLOCK:
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_ANGLE_7_OCLOCK))->Render(x, y);
		break;
	case DIR_8_OCLOCK:
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_ANGLE_8_OCLOCK))->Render(x, y);
		break;
	case DIR_9_OCLOCK:
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_ANGLE_9_OCLOCK))->Render(x, y);
		break;
	case DIR_10_OCLOCK:
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_ANGLE_10_OCLOCK))->Render(x, y);
		break;
	case DIR_11_OCLOCK:
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_ANGLE_11_OCLOCK))->Render(x, y);
		break;
	case DIR_12_OCLOCK:
		animations->Get(Get_CharANI_ID(obj->CharID(), ACT_ANGLE_12_OCLOCK))->Render(x, y);
		break;
	}
}

void State_Turret_Active::Update(DWORD dt)
{
	if (_nextState != -1)
		return;

	Game_Character* obj = (Game_Character*)_srcObj;

	// do something
}

void State_Turret_Active::KeyPressed_Hide()
{
	if (_nextState == -1)
		_nextState = STATE_HIDE;
}

void State_Turret_Active::KeyPressed_Shoot()
{
	Game_Character* obj = (Game_Character*)_srcObj;

	obj->Shoot(_currentAngle);
}