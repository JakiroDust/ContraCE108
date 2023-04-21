#pragma once
#include "Game_MovableEnemy.h"

#define REDGUNNER_BASE_WIDTH 20
#define REDGUNNER_BASE_HEIGHT 32
#define REDGUNNER_JUMP_WIDTH 20
#define REDGUNNER_JUMP_HEIGHT 28
#define REDGUNNER_SWIM_WIDTH 20
#define REDGUNNER_SWIM_HEIGHT 32

class Enemy_RedGunner : public Game_MovableEnemy
{
	private:
		void UpdateState() override;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
	public:
		Enemy_RedGunner(float x, float y, int z) : Game_MovableEnemy(x, y, z, REDGUNNER_BASE_WIDTH, REDGUNNER_BASE_HEIGHT)
		{
			_moveSpd = 0.08f;
		}
		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		int CharID() override;
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_MovableObject::OnNoCollision(dt); }
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override;

		void GetCustomSize(int state, int& width, int& height) override;
		void Execute_DieAction() override;
};

