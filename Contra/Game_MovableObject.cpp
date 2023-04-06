#include "Game_MovableObject.h"

const float Game_MovableObject::jumpVector = 0.25f;

bool Game_MovableObject::isDie()
{
	return _die;
}

float Game_MovableObject::footerX()
{
	return _x + _width / 2;
}

float Game_MovableObject::footerY()
{
	return _y + _height;
}

float Game_MovableObject::realX(float x)
{
	return x - _width / 2;
}

float Game_MovableObject::realY(float y)
{
	return y - _height;
}

void Game_MovableObject::moveLeft()
{
	_faceLeft = true;
	_vx = -_moveSpd;
}

void Game_MovableObject::moveRight()
{
	_faceLeft = false;
	_vx = _moveSpd;
}

void Game_MovableObject::jump()
{
	_jumpForce = 30;
}

void Game_MovableObject::forceDie()
{
	_die = true;
}

void Game_MovableObject::UpdateJumpState()
{
	if (_jumpForce > 0)
	{
		_vy = -jumpVector;
		_jumpForce --;
	}
	else
	{
		_jumpForce = 0;
		_vy = jumpVector;
	}
}

void Game_MovableObject::teleport(float x, float y)
{
	_x = realX(x);
	_y = realY(y);
}

void Game_MovableObject::ResetStateParams()
{
	Game_ObjectBase::ResetStateParams();
	_swim = false;
	_onGround = false;
}

void Game_MovableObject::Update(DWORD dt)
{
	UpdateDefault();
}
void Game_MovableObject::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	UpdateDefault();
}

void Game_MovableObject::UpdateDefault()
{
	if (_gravity)
	{
		UpdateJumpState();
	}
	if (_ForceX != 0)
	{
		if (_ForceX > 0)
		{
			_ForceX--;
			moveLeft();
		}
		else
		{
			_ForceX++;
			moveRight();
		}
	}
}

void Game_MovableObject::OnNoCollision(DWORD dt)
{
	Game_ObjectBase::OnNoCollision(dt);
	_onGround = false;
}

void Game_MovableObject::OnCollisionWith(PCOLLISIONEVENT e) 
{
	Game_ObjectBase::OnCollisionWith(e);
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		if (e->ny < 0) _onGround = true;
		if (e->ny > 0) _jumpForce = 0;
	}
}