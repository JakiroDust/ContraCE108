#pragma once
#include "Game_StationEnemy.h"
#include "Equip_EnemyGun_Turret.h"

#define CANNON_BASE_WIDTH 32
#define CANNON_BASE_HEIGHT 32
#define CANNON_TRIGGER_RANGE_X 200
#define CANNON_TRIGGER_RANGE_Y 200
#define CANNON_ROTATE_CD 150

// This enemy only face left
class Enemy_Cannon : public Game_StationEnemy
{
	private:
		void UpdateState() override;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
		int _lockDir = 0;
		DWORD _rotate_CD = 0;
		void Cleaning() override { Game_StationEnemy::Cleaning(); }
	public:
		Enemy_Cannon(float x, float y, int z, bool faceLeft = true) : Game_StationEnemy(x, y, z, CANNON_BASE_WIDTH, CANNON_BASE_HEIGHT)
		{
			_weapon = new Equip_EnemyGun_Turret();
			_hp = 20;
			_station_12DIR = true;
			_faceLeft = faceLeft;
			_gravity = false;
		}
		~Enemy_Cannon() {
			Game_StationEnemy::~Game_StationEnemy();
		};

		void Shoot(int DIR) override;

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override { Game_StationEnemy::Update(dt, coObjects); }
		int CharID() override;
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_StationEnemy::OnNoCollision(dt); }
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override { Game_StationEnemy::OnCollisionWith(e); }

		void GetCustomSize(int state, int& width, int& height) override;
		void Execute_DieAction() override;
};

