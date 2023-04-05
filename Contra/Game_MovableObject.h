#pragma once
#include "Game_ObjectBase.h"
#include <string>

class Game_MovableObject : public Game_ObjectBase
{
protected:
	/// PROPERTIES

	// Moving speed of entity
	float _moveSpd = 1;
	// When value above 0, entity will float.
	float _jumpForce = 0;


	/// state

	bool _faceLeft = false;
	bool _swim = false;
	bool _immortal = false;
	bool _ghost = false;
	bool _onAir = false;
	bool _die = false;
	string _state = "idle";

	/// function
	void UpdateJumpState();
public:
	/// STATIC

	// World variable to determine
	// how fast jumpForce will be modified.
	static const int jumpVector = 2;

	// CONSTRUCTOR

	Game_MovableObject(float x, float y, int z, int width, int height) : Game_ObjectBase(x, y, z, width, height) {}

	//-------------------------------------------------------------------------------
	/// INHERITED

	int baseType() { return TYPE_MOVABLE; }
	
	// Get hitbox
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override { Game_ObjectBase::GetBoundingBox(left, top, right, bottom); }
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	int IsCollidable() override { return 1; }
	// When no collision has been detected (triggered by CCollision::Process)
	void OnNoCollision(DWORD dt) override { Game_ObjectBase::OnNoCollision(dt); }
	// When collision with an object has been detected (triggered by CCollision::Process)
	void OnCollisionWith(PCOLLISIONEVENT e) override { Game_ObjectBase::OnCollisionWith(e); }
	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	bool IsBlocking() override { return 0; }

	// Key event handler
	virtual void KeyDownEventHandler(int KeyCode) override {}
	// Key event handler
	virtual void KeyUpEventHandler(int KeyCode) override {}

	//-------------------------------------------------------------------------------

	/// GET & SET

	// alternative horizonal position.
	// It will be determine based on the point in the middle of sprite footer.
	float mapX();
	// alternative vertical position.
	// It will be determine based on the point in the middle of sprite footer.
	float mapY();
	// Convert mapX to real x.
	float realX(float x);
	// Convert mapY to real y.
	float realY(float y);

	/// STATE

	virtual bool isDie();

	/// UPDATE
	
	void Update(DWORD dt) override{}
	void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override {}

	// Render

	void Render() { Game_ObjectBase::Render(); }

	/// ACTION



	// Override teleport function.
	// Use entity x,y pos instead of real x,y pos.
	virtual void teleport(float x, float y);
	virtual void moveLeft();
	virtual void moveRight();
	virtual void jump();
	virtual void forceDie();
};

