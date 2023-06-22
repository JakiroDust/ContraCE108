#pragma once
#include "Obj_EnemyBullet_N.h"

#define ENEMYBULLET_B_WIDTH 16
#define ENEMYBULLET_B_HEIGHT 16

class Obj_EnemyBullet_Blast : public Game_Bullet
{
	private:
		void Init()
		{
			_moveSpd = 0.08f;
			_OwnerID = B_OWNER_ENEMY;
			_Damage = 1;
			_SpriteId = ANI_ALIEN_BASE_BULLET;
		}

	public:
		// If type = true, use point (x,y) instead of vx, vy
		// vx, vy will be caculated so that bullet can move toward that point. 
		Obj_EnemyBullet_Blast(float x, float y, int z, float vx, float vy, bool type = false) : Game_Bullet(x, y, z, ENEMYBULLET_B_WIDTH, ENEMYBULLET_B_HEIGHT)
		{
			Init();
			if (type)
				SetTargetPos(vx, vy);
			else
				SetVector(vx, vy);

		}

		Obj_EnemyBullet_Blast(float x, float y, int z, float degree) : Game_Bullet(x, y, z, ENEMYBULLET_N_WIDTH, ENEMYBULLET_N_HEIGHT)
		{
			Init();
			SetAngle(degree);
		}
};

