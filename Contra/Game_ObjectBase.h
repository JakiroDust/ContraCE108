#pragma once

#define TYPE_STATIC 0
#define TYPE_MOVABLE 1

using namespace std;
#include "Game_Collision.h"
#include "Animations.h"
#include "debug.h"

class Game_ObjectBase
{
protected:
	/// POS

	// horizonal position, base on current map
	float _x;
	// vertical position, base on current map
	float _y;
	// Value use to determine with object will be draw first
	// Object with lowest value will be drawn first.
	int _z;

	float _vx = 0;
	float _vy = 0;

	/// PROPERTIES

	int _width;
	int _height;

	// LOGIC

	bool _isDeleted = false;

	// RENDER 

	int _SpriteId = 0;
	bool _needRender = true;

	/// PROTECTED FUNCTIONS

public:
	Game_ObjectBase(float x = 0, float y = 0, int z = 0, int width = 0, int height = 0);

	// GET SET FUNCTIONS

	float x() { return _x; }
	float y() { return _y; }
	int z() { return _z; }
	void SetPosition(float x, float y) { this->_x = x, this->_y = y; }
	void SetSpeed(float vx, float vy) { this->_vx = vx, this->_vy = vy; }
	void GetPosition(float& x, float& y) { x = this->_x; y = this->_y; }
	void GetSpeed(float& vx, float& vy) { vx = this->_vx; vy = this->_vy; }
	void GetCenterPoint(float& x, float& y) { x = _x + _width / 2; y = _y + _height / 2; }

	// Draw object to screen
	virtual void Render();
	virtual void SetNeedRender(bool b) { _needRender = b; }
	virtual bool NeedRender() { return _needRender; }

	// Movable object or Static Object
	virtual int baseType() = 0;

	// UPDATE

	virtual void Update(DWORD dt) {}
	virtual void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) {}

	// COLLISION

	// Get hitbox
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	virtual int IsCollidable() { return 0; }
	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {}
	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(PCOLLISIONEVENT e) {}
	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual bool IsBlocking() { return 0; }


	// Key event handler
	virtual void KeyDownEventHandler(int KeyCode) {}
	// Key event handler
	virtual void KeyUpEventHandler(int KeyCode) {}

	virtual void DeleteThis() { _isDeleted = true; }
	bool IsDeleted() { return _isDeleted; }
};

