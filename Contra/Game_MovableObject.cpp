#include "Game_MovableObject.h"



bool Game_MovableObject::isDie()
{
	return _die;
}

float Game_MovableObject::mapX()
{
	return _x + _width / 2;
}

float Game_MovableObject::mapY()
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
	_jumpForce = 150;
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
		_jumpForce -= jumpVector;
	}
	else
	{
		_vy = jumpVector;
	}
}

void Game_MovableObject::teleport(float x, float y)
{
	_x = realX(x);
	_y = realY(y);
}

void Game_MovableObject::Update(DWORD dt)
{
	if (_gravity) {
		UpdateJumpState();
	}
}
void Game_MovableObject::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (_gravity) {
		UpdateJumpState();
	}
}