#pragma once
#include "Game_Bullet.h"

class Obj_Bullet_Rifle :  public Game_Bullet
{
	private:
		void Init()
		{
			_moveSpd = 0.5;
			_OwnerID = B_OWNER_PLAYER;
		}

	public:
		Obj_Bullet_Rifle(float x, float y, int z, int width, int height, float targetX, float targetY) : Game_Bullet(x, y, z, width, height)
		{
			SetTargetPos(targetX, targetY);
			Init();
		}

		Obj_Bullet_Rifle(float x, float y, int z, int width, int height, float degree) : Game_Bullet(x, y, z, width, height)
		{
			SetAngle(degree);
			Init();
		}


};

