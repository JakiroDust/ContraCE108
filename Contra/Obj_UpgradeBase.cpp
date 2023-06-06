#include "Obj_UpgradeBase.h"
#include "Game_DeadlyBlock.h"
#include "Game_Player.h"
#include "Obj_UpgradeBase.h"
#include "ScreenManager.h"

void Obj_UpgradeBase::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_SpecialObject::Update(dt, coObjects);
}

void Obj_UpgradeBase::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_SpecialObject::OnCollisionWith(e);
	if (!_die && dynamic_cast<Game_Player*>(e->obj))
	{
		applyUpgrade();
		forceDie();
	}
}

void Obj_UpgradeBase::Render()
{
	Game_ObjectBase::Render();
}