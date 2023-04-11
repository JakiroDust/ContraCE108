#pragma once
#include "Game_MovableObject.h"
//#include "Contra_GET_ANI.h"

using namespace std;

class Game_Character : public Game_MovableObject
{
	protected:
		int _hp = 1;
		bool _jumpDown = false;

	public:

		Game_Character(float x, float y, int z, int width, int height) : Game_MovableObject(x, y, z, width, height)
		{
			_needScanCollision = true;
		}
		//-------------------------------------------------------------------------------
		/// INHERITED

		// Get hitbox
		void GetBoundingBox(float& left, float& top, float& right, float& bottom) override { Game_ObjectBase::GetBoundingBox(left, top, right, bottom); }
		// Collision ON or OFF ? This can change depending on object's state. For example: die
		int IsCollidable() override { return 1; }
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt);
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override;
		// Is this object blocking other object? If YES, collision framework will automatically push the other object
		bool IsBlocking() override { return 0; }
		// Can this object ingore blocking object and move through it?
		// If YES, collision framework will skip this collision event.
		
		virtual bool IgnoreBlocking() { return 0; }
		// Key event handler
		virtual void KeyDownEventHandler(int KeyCode) override {}
		// Key event handler
		virtual void KeyUpEventHandler(int KeyCode) override {}

		void Update(DWORD dt) override { Game_MovableObject::Update(dt); }
		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override { Game_MovableObject::Update(dt, coObjects); }
		//-------------------------------------------------------------------------------

		// GET & SET

		bool IsJumpDown() { return _jumpDown; }
		void SetJumpDown(bool b) { _jumpDown = b; }
		virtual int CharID() { return -1; }
};





