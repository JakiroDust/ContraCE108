#include "Game_MovableObject.h"

const float Game_MovableObject::JUMP_VECTOR = 0.15f;

bool Game_MovableObject::isDie()
{
	return _die;
}

float Game_MovableObject::footerX()
{
	return _x + ceilf((float)_width / 2) - 1;
}

float Game_MovableObject::footerY()
{
	return _y - _height + 1;
}

float Game_MovableObject::realX(float x)
{
	return floorf(x - ceilf((float)_width / 2) + 1);
}

float Game_MovableObject::realY(float y)
{
	return floorf(y + _height - 1);
}

void Game_MovableObject::moveLeft()
{
	if (!_lockFace)
		_faceLeft = true;
	_vx = -_moveSpd;
}

void Game_MovableObject::moveRight()
{
	if (!_lockFace)
		_faceLeft = false;
	_vx = _moveSpd;
}

void Game_MovableObject::moveUp()
{
	if (_gravity)
		return;
	_vy = _moveSpd;
}

void Game_MovableObject::moveDown()
{
	if (_gravity)
		return;
	_vy = -_moveSpd;
}

void Game_MovableObject::jump()
{
	// only allow when this object is affected by gravity
	if (!_gravity)
		return;
	_jumpForce = GetJumpForce();
}

void Game_MovableObject::forceDie()
{
	_die = true;
}

void Game_MovableObject::UpdateJumpState(DWORD dt)
{
	if (_jumpForce > 0)
	{
		if (_jumpForce < JUMP_VECTOR * dt)
		{
			_vy = _jumpForce/dt;
			_jumpForce = 0;
		}
		else
		{
			_jumpForce -= JUMP_VECTOR * dt;
			_vy = JUMP_VECTOR;
		}
		
	}
	else
	{
		_jumpForce = 0;
		_vy = -JUMP_VECTOR;
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
	UpdateDefault(dt);
}
void Game_MovableObject::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	UpdateDefault(dt);
}

void Game_MovableObject::UpdateDefault(DWORD dt)
{
	if (_gravity)
	{
		UpdateJumpState(dt);
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
		if (e->ny > 0) _onGround = true;
		if (e->ny < 0) _jumpForce = 0; 
	}
}