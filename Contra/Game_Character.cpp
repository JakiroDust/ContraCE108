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
		&& footerY() - e->obj->y() < _height / 2.0)
	{
		if (e->nx < 0)
		{
			_jumpForce = (footerY() - e->obj->y()) / (JUMP_VECTOR * 4) + 1;
			_jumpForce = floorf(_jumpForce);
			_ForceX = -10;
		}
		else
		{
			_jumpForce = (footerY() - e->obj->y()) / (JUMP_VECTOR * 4) + 1;
			_jumpForce = floorf(_jumpForce);
			_ForceX = 10;
		}
	}
}

void Game_Character::AddAction(int KeyCode1, int KeyCode2)
{
	pair<int, int> p(KeyCode1,KeyCode2);
	_ActionQueue.push_back(p);
}

void Game_Character::ExecuteAction()
{
	if (_ActionQueue.size() == 0)
	{
		KeyReleaseAll();
		return;
	}
	pair<int,int> action = _ActionQueue[0];
	_ActionQueue.erase(_ActionQueue.begin());
	if (action.first == -1)
	{
		KeyReleaseAll();
		return;
	}
	KeyDownEventHandler(action.first);
	if (action.second != -1)
		KeyDownEventHandler(action.second);
}