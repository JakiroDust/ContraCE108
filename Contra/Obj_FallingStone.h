#pragma once
#include "Game_SpecialObject.h"

#define STONE_WIDTH 32
#define STONE_HEIGHT 32
#define STONE_EMERGE_INTERVAL 600
#define STONE_SHAKE_RANGE 5
#define STONE_BOUNCE_HEIGHT 24
#define STONE_FALLING_SPEED -0.05f

class Obj_FallingStone : public Game_SpecialObject
{
	private:
		void UpdateState() override;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
		bool _hitPlatformFlag = false;
		DWORD _EmergeTick = STONE_EMERGE_INTERVAL;
		float _baseX = 0;
		bool _finishEmerge = false;
		vector<int> _touchList;
		void Cleaning() override
		{
			_touchList.clear();
		}
	public:
		Obj_FallingStone(float x, float y, int z) : Game_SpecialObject(x, y, z, STONE_WIDTH, STONE_HEIGHT)
		{
			_moveSpd = 0.05f;
			_haveStandby = true;
			_BodyDamage = false;
			_faceLeft = true;
			_ghost = true;
			_gravity = false;
			_baseX = x;
			_ForceX = -STONE_SHAKE_RANGE;
		}
		~Obj_FallingStone() {
			Game_SpecialObject::~Game_SpecialObject();
			Cleaning();
		};
		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		int CharID() override;
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_MovableObject::OnNoCollision(dt); }
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override;

		void Execute_DieAction() override {}
};

