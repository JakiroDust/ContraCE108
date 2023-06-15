#pragma once
#include "Game_Bullet.h"

#define ENEMYBULLET_SBOMB_WIDTH 8
#define ENEMYBULLET_SBOMB_HEIGHT 8
#define SBOMB_MAX_TRAVEL_DISTANCE 250
#define SBOMB_SPREAD_X 200
#define SBOMB_SPREAD_Y 100

class Obj_EnemyBullet_SBomb : public Game_Bullet
{
	protected:
		float _travelled_Distance = 0;
		int _bypassPlatformID = -1;
		bool _explodeFlag = false;
		void Init()
		{
			_moveSpd = 0.08f;
			_OwnerID = B_OWNER_ENEMY;
			_Damage = 1;
			_SpriteId = CONTRA_BULLET_ANI_BULLET_S;
		}

		void Create_ExplodeAnimation();
	public:
		// If type = true, use point (x,y) instead of vx, vy
		// vx, vy will be caculated so that bullet can move toward that point. 

		Obj_EnemyBullet_SBomb(float x, float y, int z) : Game_Bullet(x, y, z, ENEMYBULLET_SBOMB_WIDTH, ENEMYBULLET_SBOMB_HEIGHT)
		{
			Init();
			_vy = _moveSpd;
			_needScanCollision = true;
		}

		~Obj_EnemyBullet_SBomb()
		{
			Cleaning();
		}

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		bool CollideBlockerCondition(DWORD dt, PCOLLISIONEVENT e) override;
		bool IsExplosive() override { return true; }
		void Execute_BeforeDelete() override;
		void Execute_ExplodingEffect() override;
};

class Obj_EnemyBullet_SBomb_Phase2 : public Obj_EnemyBullet_SBomb
{
	private:
		void Init()
		{
			_moveSpd = 0.1f;
			_OwnerID = B_OWNER_ENEMY;
			_Damage = 1;
			_SpriteId = CONTRA_BULLET_ANI_BULLET_M;
		}
	public:
		Obj_EnemyBullet_SBomb_Phase2(float x, float y, int z, float ForceX, float ForceY) : Obj_EnemyBullet_SBomb(x, y, z)
		{
			Init();
			_vy = _moveSpd;
			_ForceX = ForceX;
			_ForceY = ForceY;
			_needScanCollision = true;
		}

		~Obj_EnemyBullet_SBomb_Phase2()
		{
			Cleaning();
		}

		void Execute_BeforeDelete() override;
};

