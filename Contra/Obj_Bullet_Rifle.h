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
		// If type = true, use point (x,y) instead of vx, vy
		// vx, vy will be caculated so that bullet can move toward that point. 
		Obj_Bullet_Rifle(float x, float y, int z, int width, int height, float vx, float vy, bool type = false) : Game_Bullet(x, y, z, width, height)
		{
			if (type)
				SetTargetPos(vx, vy);
			else
				SetSpeed(vx, vy);
			Init();
		}

		Obj_Bullet_Rifle(float x, float y, int z, int width, int height, float degree) : Game_Bullet(x, y, z, width, height)
		{
			SetAngle(degree);
			Init();
		}


};

