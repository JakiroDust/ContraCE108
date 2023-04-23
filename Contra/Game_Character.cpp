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
		//_jumpForce = (footerY() - e->obj->y()) / (JUMP_VECTOR * 4) + 1
		_jumpForce = (footerY() - e->obj->y()) + _height / 4.0f;
		_jumpForce = floorf(_jumpForce);
		if (e->nx < 0)
		{
			_ForceX = -10;
		}
		else
		{
			_ForceX = 10;
		}
	}
}

void Game_Character::Shoot()
{
	float x, y;
	this->GetCenterPoint(x, y);
	float vx=0, vy=0;
	//GET DIR
	int dir = DIR_TOP;
	x += _spawnBulletHelper[dir][X];
	y += _spawnBulletHelper[dir][Y];
	//Get gun or not or whatever 
	// gun.gunshoot(x,y,dir)
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

Game_Character::Game_Character(float x, float y, int z, int width, int height) : Game_MovableObject(x, y, z, width, height)
{
	_needScanCollision = true;

	//init default _spawnBulletHelper;
	for (int i = 1; i <= 9; i++)
		_spawnBulletHelper[i] = vector<float>(2, 0);

	_spawnBulletHelper[DIR_TOP][X] = 0;
	_spawnBulletHelper[DIR_TOP][Y] = 10;

	_spawnBulletHelper[DIR_TOP_RIGHT][X] = 7;
	_spawnBulletHelper[DIR_TOP_RIGHT][Y] = 7;
	
	_spawnBulletHelper[DIR_RIGHT][X] = 10;
	_spawnBulletHelper[DIR_RIGHT][Y] = 0;

	_spawnBulletHelper[DIR_BOTTOM_RIGHT][X] = 7;
	_spawnBulletHelper[DIR_BOTTOM_RIGHT][Y] = -7;

	_spawnBulletHelper[DIR_BOTTOM][X] = 0;
	_spawnBulletHelper[DIR_BOTTOM][Y] = -10;

	_spawnBulletHelper[DIR_BOTTOM_LEFT][X] = -7;
	_spawnBulletHelper[DIR_BOTTOM_LEFT][Y] = -7;

	_spawnBulletHelper[DIR_LEFT][X] = -10;
	_spawnBulletHelper[DIR_LEFT][Y] = 0;

	_spawnBulletHelper[DIR_TOP_LEFT][X] = -7;
	_spawnBulletHelper[DIR_TOP_LEFT][Y] = 7;

}
