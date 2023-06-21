#include "Equip_EnemyGun_AlienBase.h"
#include "Obj_EnemyBullet_Blast.h"
#include "ScreenManager.h"
#include "Game_Character.h"

void Equip_EnemyGun_AlienBase::Fire(float& x, float& y, float& vx, float& vy, bool type)
{
	unique_ptr<Obj_EnemyBullet_Blast> bullet(new Obj_EnemyBullet_Blast(x, y, Z_INDEX_BULLET, vx, vy, type));
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	scene->add_object(move(bullet));
}

void Equip_EnemyGun_AlienBase::Fire(float& x, float& y, int DIR)
{
	unique_ptr<Obj_EnemyBullet_Blast> bullet;
	float vx, vy;
	switch (DIR)
	{
	case DIR_TOP:
		vx = 0; vy = 1;
		break;
	case DIR_BOTTOM:
		vx = 0; vy = -1;
		break;
	case DIR_LEFT:
		vx = -1; vy = 0;
		break;
	case DIR_RIGHT:
		vx = 1; vy = 0;
		break;
	case DIR_TOP_LEFT:
		vx = -1; vy = 1;
		break;
	case DIR_TOP_RIGHT:
		vx = 1; vy = 1;
		break;
	case DIR_BOTTOM_LEFT:
		vx = -1; vy = -1;
		break;
	case DIR_BOTTOM_RIGHT:
		vx = 1; vy = -1;
		break;
	default:
		break;
	}
	bullet = unique_ptr<Obj_EnemyBullet_Blast>(new Obj_EnemyBullet_Blast(x, y, Z_INDEX_BULLET, vx, vy));
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	scene->add_object(move(bullet));
}