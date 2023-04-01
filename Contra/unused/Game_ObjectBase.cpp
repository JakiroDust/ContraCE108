#include "Game_ObjectBase.h"
using namespace std;

Game_ObjectBase::Game_ObjectBase(int x, int y, int z, int width, int height)
{
	_x = x;
	_y = y;
	_z = z;
	_width = width;
	_height = height;
}

int Game_ObjectBase::x()
{
	return _x;
}

int Game_ObjectBase::y()
{
	return _y;
}

int Game_ObjectBase::z()
{
	return _z;
}

void Game_ObjectBase::teleport(int x, int y)
{
	_x = x;
	_y = y;
}

void Game_ObjectBase::updateSprite()
{
	updateFrame();
}

void Game_ObjectBase::updateFrame()
{
	if (_frameMax == 0)
	{
		return;
	}
	// check frame interval
	if (_frameTimer != _frameInterval)
	{
		_frameTimer++;
	} 
	else
	{
		// finish frame CD
		_frameTimer = 0;
		// check frame
		if (_frameCurrent != _frameMax)
		{
			_frameCurrent++;
		}
		else
		{
			_frameCurrent = 0;
		}
	}
}

void Game_ObjectBase::draw()
{
	//sprite->draw(_x,_y,_frameCurrent);
}