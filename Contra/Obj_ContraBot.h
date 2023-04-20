#pragma once
#include "Game_Enemy.h"

class Obj_ContraBot : public Game_Enemy
{
	private:
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
	public:
		Obj_ContraBot(float x, float y, int z) : Game_Enemy(x, y, z, 20, 32)
		{
			_moveSpd = 0.1f;
		}

		int CharID() override;
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt);
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override;
		void GetCustomSize(int state, int& width, int& height) override;
};

