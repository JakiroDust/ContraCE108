#include "Game_Character.h"
#include "Game_Water.h"
#include "Game_Platform.h"
#include "Game_Collision.h"

void Game_Character::OnNoCollision(DWORD dt)
{
	Game_MovableObject::OnNoCollision(dt);
}


void Game_Character::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_MovableObject::OnCollisionWith(e);
	if (_onGround && dynamic_cast<Game_Water*>(e->obj))
	{
		_swim = true;
	} 

	float test = footerY();

	if (dynamic_cast<Game_Platform*>(e->obj)
		&& footerY() <= e->obj->y()
	){
		_onGround = true;
	}

	if (e->nx != 0 && _onGround && dynamic_cast<Game_Terrain*>(e->obj) && !dynamic_cast<Game_Water*>(e->obj)
		&& footerY() - e->obj->y() < _height / 2)
	{
		if (e->nx < 0)
		{
			_jumpForce = (footerY() - e->obj->y()) / (jumpVector * 4) + 1;
			_jumpForce = floorf(_jumpForce);
			_ForceX = -10;
		}
		else
		{
			_jumpForce = (footerY() - e->obj->y()) / (jumpVector * 4) + 1;
			_jumpForce = floorf(_jumpForce);
			_ForceX = 10;
		}
	}
}