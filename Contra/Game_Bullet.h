#pragma once
#include "Game_MovableObject.h"
#include "Contra_ANI_ID.h"

#define B_OWNER_PLAYER 0
#define B_OWNER_ENEMY 1
#define B_SPAWN_MODE_TARGETPOS 1
#define B_SPAWN_MODE_SETSPEED 0

#define B_VALUE_Z 2

class Game_Bullet : public Game_MovableObject
{
	protected:
		// Used by other objects.
		// Base on OwnerID, objects will ignore this bullet or not.
		int _OwnerID = 0;
		int _Damage = 1;
	public:
		Game_Bullet(float x, float y, int z, int width, int height) : Game_MovableObject(x, y, z, width, height)
		{
			_needScanCollision = false;
			_moveSpd = 0.5;
		}

		// Used by other objects.
		// Base on OwnerID, objects will ignore this bullet or not.
		int OwnerID() { return _OwnerID; }
		int Damage() { return _Damage; }

		// Can this object ingore blocking object and move through it?
		// If YES, collision framework will skip this collision event.
		bool IgnoreBlocking() override { return 1; }

		void Update(DWORD dt) override;
		void SetAngle(float degree);
		void SetTargetPos(float x, float y);
		void SetVector(float vx, float vy);
};

