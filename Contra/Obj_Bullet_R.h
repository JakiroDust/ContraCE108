#pragma once
#include "Game_Bullet.h"

#define BULLET_N_WIDTH 5
#define BULLET_N_HEIGHT 5

class Obj_Bullet_R : public Game_Bullet
{
	private:
		void Init()
		{
			_moveSpd = 0.3f;
			_OwnerID = B_OWNER_PLAYER;
			_Damage = 1;
			_SpriteId = CONTRA_BULLET_ANI_BASE_LEFT;
		}

	public:
		// If type = true, use point (x,y) instead of vx, vy
		// vx, vy will be caculated so that bullet can move toward that point. 
		Obj_Bullet_R(float x, float y, int z, float vx, float vy, bool type = false) : Game_Bullet(x, y, z, BULLET_N_WIDTH, BULLET_N_HEIGHT)
		{
			Init();
			if (type)
				SetTargetPos(vx, vy);
			else
				SetVector(vx, vy);
		}

		Obj_Bullet_R(float x, float y, int z, float degree) : Game_Bullet(x, y, z, BULLET_N_WIDTH, BULLET_N_HEIGHT)
		{
			Init();
			SetAngle(degree);
		}

};

