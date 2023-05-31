#include "Game_Character.h"
#include "Game_Water.h"
#include "Game_Platform.h"
#include "Game_Collision.h"
#include "Game_TestBox.h"
#include "Scene_Battle.h"
#include "Game_DeadlyBlock.h"
#include "Obj_MovingStone.h"

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
	ApplyExternalForce();
}

void Game_Character::OnNoCollision(DWORD dt)
{
	Game_MovableObject::OnNoCollision(dt);
}

#define CLIMP_UP_TERRAIN_SCALE_Y_X 0.25f

void Game_Character::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_MovableObject::OnCollisionWith(e);
	if (_onGround && dynamic_cast<Game_Water*>(e->obj))
	{
		_swim = true;
		return;
	} 

	//if (dynamic_cast<Game_Platform*>(e->obj)
	//	&& footerY() >= e->obj->y()
	//){
	//	_onGround = true;
	//}

	if (dynamic_cast<Obj_MovingStone*>(e->obj)
		&& footerY() >= e->obj->y()
		) {
		float vx, vy;
		e->obj->GetSpeed(vx, vy);
		_external_vx += vx;
		_external_vy += vy;
		return;
	}

	// climb up
	if (e->nx != 0 && _onGround && dynamic_cast<Game_Terrain*>(e->obj)
		&& e->obj->y() - footerY() <= CHARACTER_JUMP_ON_HEIGHT)
	{
		// character is under water
		teleport(_x, e->obj->y() + _height + CHARACTER_JUMP_ON_HEIGHT / 3.0f);
		float forceXValue = abs(e->obj->y() - footerY()) / CLIMP_UP_TERRAIN_SCALE_Y_X;
		if (e->nx < 0)
		{
			_ForceX = forceXValue;
		}
		else
		{
			_ForceX = -forceXValue;
		}
	}
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
	unique_ptr<Game_TestBox>testbox(new Game_TestBox(_x, _y - _height - 12, _z, _width, 8, 0, 0));
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	vector<int> id_list = ScreenManager::GetInstance()->Screen()->Get_ObjectsID_InsideScreen(scene->spatial.get(), GET_OBJECTS_RANGE);
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
		//Check if under player have any terrain
		if (dynamic_cast<Game_DeadlyBlock*>(e->obj) || dynamic_cast<Game_SweeperBlock*>(e->obj))
		{
			canJumpDown = false;
			break;
		}

		if (dynamic_cast<Game_Platform*>(e->obj)
			|| dynamic_cast<Game_Blocker*>(e->obj)
			|| dynamic_cast<Game_Water*>(e->obj))
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

	pair<int,int> action = (_ActionQueue[0]);
	if (action.first == DIK_PAUSE)
	{
		KeyReleaseAll();
		if (action.second > 1)
			_ActionQueue[0].second--;
		else 
			_ActionQueue.erase(_ActionQueue.begin());
		return;
	}

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

