#pragma once
#include "Game_Character.h"

class Game_Enemy : public Game_Character
{
	protected:
		void UpdateState() override;
		virtual void UpdateBehavior(DWORD dt, vector<Game_ObjectBase*>* coObjects = NULL);
		void KeyReleaseAll() override;
	public:
		Game_Enemy(float x, float y, int z, int width, int height) : Game_Character(x, y, z, width, height)
		{
			_moveSpd = 0.1f;
		}

		void Render() override;
		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		void KeyDownEventHandler(int KeyCode) override;
		void KeyUpEventHandler(int KeyCode) override;
		void KeyStateHandler(BYTE* state) override;
		void getPlayerLoc(float&, float&);
		void spawnBullet();
		//============================================================================================
		// INHERITED

		// Collision ON or OFF ? This can change depending on object's state. For example: die
		int IsCollidable() override { return 1; }
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt);
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override;
		// Sprite ID
		int CharID() override;
};


