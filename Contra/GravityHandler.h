#pragma once
#include "Game.h"
#define GAME_GRAVITY 0.0015f
#define FALL_SPEED	 0.150f
#define JUMP_Y_START 0.6f
class GravityHandlerBase
{
protected:
	const float ay = GAME_GRAVITY;
	
public:
	float vy;
	GravityHandlerBase()
	{
		vy = 0;
	}
	void setVy(float newVy) { vy = newVy; }

};
class GravityHandlerOff : virtual public GravityHandlerBase
{
public:
	GravityHandlerOff() :GravityHandlerBase() {};

};
class GravityHandlerOn : virtual public GravityHandlerBase
{
protected:
	float _fake_vy = JUMP_Y_START;
	GravityHandlerOn() 
	{
		vy = FALL_SPEED;
	}
	
	

	void isOnPlatform_Y()
	{
		vy = 0;
		_fake_vy = 0;
	}
	void update_vy(DWORD& dt)
	{
		_fake_vy += ay * dt;
		if (_fake_vy == 0)
			vy = 0;
		else	if (_fake_vy > 0)
			vy = FALL_SPEED;
		else    if (_fake_vy < 0)
			vy = -FALL_SPEED;
	}
	void jumped_Y()
	{
		_fake_vy = -JUMP_Y_START;
		vy = -FALL_SPEED;
	}
};

