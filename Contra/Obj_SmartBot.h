#pragma once
#include "Game_Enemy.h"

class Obj_SmartBot : public Game_Enemy
{
	private:
		Mapper* _map;
		vector<PTERRAINNODE> _path;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
	public:
		Obj_SmartBot(float x, float y, int z) : Game_Enemy(x, y, z, 20, 32) 
		{
			_map = new Mapper(this);
			_moveSpd = 0.08f;
			_ghost = true;
		}
		~Obj_SmartBot()
		{
			delete _map;
		}

		int CharID() override;
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt);
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override;

		void GetCustomSize(int state, int& width, int& height) override;
};

// This object will follow player automatically.