#include "Game_Character.h"
#include "Game_Water.h"
#include "Game_Platform.h"
#include "Game_Collision.h"
#include "Game_TestBox.h"
#include "Scene_Battle.h"
#include "Game_DeadlyBlock.h"

void Game_Character::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_MovableObject::Update(dt, coObjects);

	if (_GunReloadInterval > dt)
	{
		_GunReloadInterval -= dt;
	}
	else if (_GunReloadInterval > 0 && _GunReloadInterval < dt)
	{
		_GunReloadInterval = 0;
	}
	if (!_moveFlag)
		_vx = 0;
	_moveFlag = false;
}

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

	if (dynamic_cast<Game_Platform*>(e->obj)
		&& footerY() >= e->obj->y()
	){
		_onGround = true;
	}

	if (e->nx != 0 && _onGround && dynamic_cast<Game_Terrain*>(e->obj) && !dynamic_cast<Game_Water*>(e->obj)
		&& e->obj->y() - footerY() < _height / 2.0)
	{
		if (_swim)
		{
			//_jumpForce = (footerY() - e->obj->y()) / (JUMP_VECTOR * 4) + 1
			_jumpForce = (e->obj->y() - footerY()) + _height / 3.0f;
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
		else
		{
			_jumpForce = (e->obj->y() - footerY()) + 4;
			_jumpForce = floorf(_jumpForce);
			if (e->nx < 0)
			{
				_ForceX = -1;
			}
			else
			{
				_ForceX = 1;
			}
		}
	}
}

void Game_Character::Shoot()
{
	return;
	/*
	float x, y;
	this->GetCenterPoint(x, y);
	float vx=0, vy=0;
	//GET DIR
	int dir = DIR_TOP;
	x += _spawnBulletHelper[dir][X];
	y += _spawnBulletHelper[dir][Y];
	*/
	//Get gun or not or whatever 
	// gun.gunshoot(x,y,dir)
}

void Game_Character::Shoot(int DIR)
{
	if (_weapon == NULL || _GunReloadInterval > 0)
		return;
	float x, y;
	GetCenterPoint(x, y);
	spawnBulletHelper::getInstance()->getSpawnCor(x, y,CharID(),DIR);
	
	/* GET OFFSET
	int dir = DIR_TOP;
	x += _spawnBulletHelper[dir][X];
	y += _spawnBulletHelper[dir][Y];
	*/

	_GunReloadInterval = _weapon->FireRate();
	_weapon->Fire(x, y, DIR);
}

void Game_Character::Shoot(float x, float y)
{
	if (_weapon == NULL || _GunReloadInterval > 0)
		return;
	float cx, cy;
	GetCenterPoint(cx, cy);

	/* GET OFFSET
	int dir = DIR_TOP;
	x += _spawnBulletHelper[dir][X];
	y += _spawnBulletHelper[dir][Y];
	*/

	_GunReloadInterval = _weapon->FireRate();
	_weapon->Fire(cx, cy, x, y, GUN_SPAWNMODE_TARGETPOS);
}

void Game_Character::moveLeft()
{
	Game_MovableObject::moveLeft();
	_moveFlag = true;
}

void Game_Character::moveRight()
{
	Game_MovableObject::moveRight();
	_moveFlag = true;
}

void Game_Character::jumpDown()
{
	unique_ptr<Game_TestBox>testbox(new Game_TestBox(_x, _y - _height - 16, _z, _width, _height, 0, 0));
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	vector<int> id_list = scene->getNearbyIDFast();
	vector<PGAMEOBJECT>* coObjects = scene->getObjectById(id_list);

	bool canJumpDown = false;

	// Make testbox move down
	testbox->SetSpeed(0, -scene->MapWidth());
	testbox->Update(1, coObjects);
	// Get Collisions and handle them.
	vector<PCOLLISIONEVENT>* coEvents = testbox->GetCollisionList();
	for (int i = 0; i < coEvents->size(); i++)
	{
		PCOLLISIONEVENT e = coEvents->at(i);
		// Check if under player have any terrain
		if (dynamic_cast<Game_DeadlyBlock*>(e->obj))
		{
			canJumpDown = false;
			break;
		}

		if (dynamic_cast<Game_Terrain*>(e->obj))
		{
			canJumpDown = true;
			break;
		}
	}
	if (canJumpDown)
		_jumpDown = true;
	else
		_jumpDown = false;
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

void Game_Character::ResetStateParams()
{
	Game_MovableObject::ResetStateParams();
}

Game_Character::Game_Character(float x, float y, int z, int width, int height) : Game_MovableObject(x, y, z, width, height)
{
	_needScanCollision = true;
}

void Game_Character::Cleaning()
{
	_ActionQueue.clear();
	delete _weapon;
	Game_MovableObject::Cleaning();
}

