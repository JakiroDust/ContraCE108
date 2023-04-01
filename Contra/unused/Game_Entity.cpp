#include "Game_Entity.h"

bool Game_Entity::isEntity()
{
	return true;
}

bool Game_Entity::isObject()
{
	return false;
}

bool Game_Entity::isDie()
{
	return _die;
}

int Game_Entity::entityX()
{
	return _x + _width/2;
}

int Game_Entity::entityY()
{
	return _y + _height;
}

int Game_Entity::realX(int x)
{
	return x - _width/2;
}

int Game_Entity::realY(int y)
{
	return y - _height;
}

void Game_Entity::moveLeft()
{
	_faceLeft = true;
	_testX = _x - _moveSpd;
}

void Game_Entity::moveRight()
{
	_faceLeft = false;
	_testX = _y + _moveSpd;
}

void Game_Entity::jump()
{
	_jumpForce = 150;
}

void Game_Entity::forceDie()
{
	_die = true;
}

void Game_Entity::updatePreCollisionTest()
{
	if (_jumpForce > 0)
	{
		_testY = _y - jumpVector;
		_jumpForce -= jumpVector;
	}
	else
	{
		if (_state != "falling" && _onAir)
		{
			_state = "falling";
		}
		if (_state == "falling")
		{
			_testY = _y + jumpVector;
		}
	}
}

void Game_Entity::teleport(int x, int y)
{
	_x = realX(x);
	_y = realY(y);
}