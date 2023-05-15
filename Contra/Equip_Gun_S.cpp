#include "Equip_Gun_S.h"
#include "ScreenManager.h"
#include "Game_Character.h"

void Equip_Gun_S::Fire(float& x, float& y, float& vx, float& vy, bool type)
{
	DebugOut(L"[INFO] Gun_N only has DIR MODE.\n");

}

void Equip_Gun_S::Fire(float& x, float& y, int DIR)
{
	if (!CanShoot())
		return;

	unique_ptr<Obj_Bullet_S> bullets[5];

	float baseAngle = 0.0f;

	switch (DIR)
	{
	case DIR_TOP:
		baseAngle = 90.0f;
		break;
	case DIR_BOTTOM:
		baseAngle = 270.0f;
		break;
	case DIR_LEFT:
		baseAngle = 180.0f;
		break;
	case DIR_RIGHT:
		baseAngle = 0.0f;
		break;
	case DIR_TOP_LEFT:
		baseAngle = 135.0f;
		break;
	case DIR_TOP_RIGHT:
		baseAngle = 45.0f;
		break;
	case DIR_BOTTOM_LEFT:
		baseAngle = 225.0f;
		break;
	case DIR_BOTTOM_RIGHT:
		baseAngle = 315.0f;
		break;
	default:
		break;
	}

	bullets[0] = unique_ptr<Obj_Bullet_S>(new Obj_Bullet_S(this, x, y, B_VALUE_Z, baseAngle));
	bullets[1] = unique_ptr<Obj_Bullet_S>(new Obj_Bullet_S(this, x, y, B_VALUE_Z, baseAngle + 20.0f));
	bullets[2] = unique_ptr<Obj_Bullet_S>(new Obj_Bullet_S(this, x, y, B_VALUE_Z, baseAngle + 40.0f));
	bullets[3] = unique_ptr<Obj_Bullet_S>(new Obj_Bullet_S(this, x, y, B_VALUE_Z, baseAngle - 20.0f));
	bullets[4] = unique_ptr<Obj_Bullet_S>(new Obj_Bullet_S(this, x, y, B_VALUE_Z, baseAngle - 40.0f));

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	for (int i = 0; i < 5; i++)
		scene->add_object(move(bullets[i]));
}