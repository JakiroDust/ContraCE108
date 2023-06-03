#include "Game_UpgradeBoxBase.h"
#include "Game_Upgrade.h"
#include "Obj_Bullet_L.h"
Game_UpgradeBoxBase::Game_UpgradeBoxBase(float x, float y, int z, int width, int height, int _type) : Game_SpecialObject(x,y,z,width,height)
{
	type = _type;
}

void Game_UpgradeBoxBase::OnCollisionWith(PCOLLISIONEVENT e)
{

// Laser
	if (!_ghost && dynamic_cast<Obj_Bullet_L*>(e->obj))
	{
		Obj_Bullet_L* bullet = ((Obj_Bullet_L*)e->obj);

		if (bullet->OwnerID() == B_OWNER_PLAYER && bullet->Test_InternalCollision(this))
		{
			if (!_immortal)
				_hp -= bullet->Damage();
			if (_HardBody)
				bullet->DeleteThis();
		}
		return;
	}

	// other bullet
	if (!_ghost && dynamic_cast<Game_Bullet*>(e->obj))
	{
		Game_Bullet* bullet = ((Game_Bullet*)e->obj);

		if (bullet->OwnerID() == B_OWNER_PLAYER)
		{
			if (!_immortal)
				_hp -= bullet->Damage();
			bullet->DeleteThis();
		}
	}
}

void Game_UpgradeBoxBase::Execute_DieAction()
{
	Game_Enemy::Execute_DieAction();
	float _x, _y;
	GetCenterPoint(_x, _y);
	Execute_BeforeDelete();
	UPGRADE::spawnUpgradeIcon(type,_x+10,_y+10);
	_isDeleted = true;
}

int Game_UpgradeBoxBase::RewardScore()
{
	return 500;
}

void Game_UpgradeBoxBase::Update(DWORD dt, vector<Game_ObjectBase*>* coObjects)
{
	//Update(dt);
	//Game_Collision::GetInstance()->Process(this, dt, coObjects);
	//if (_hp <= 0 && _ghost == false)
	//	
	ExecuteAction();
	Update(dt);
	Game_Collision::GetInstance()->Process(this, dt, coObjects);

	if (_state.get() != NULL)
		_state->Update(dt);
	UpdateState();

	if (_hp <= 0 && _ghost == false)
	{
		Execute_DieAction();
	}

	UpdateBehavior(dt, coObjects);
	ResetStateParams();
}