#include "Obj_UpgradeBase.h"
#include "Game_DeadlyBlock.h"
#include "Game_Player.h"
#include "Obj_UpgradeBase.h"
#include "ScreenManager.h"
//#include "GameManager.h"
void Obj_UpgradeBase::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_SpecialObject::Update(dt, coObjects);
}

void Obj_UpgradeBase::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_SpecialObject::OnCollisionWith(e);
	if (!_die && dynamic_cast<Game_Player*>(e->obj) && !((Game_Player*)(e->obj))->isDie())
	{
		playSFXexplode();
		applyUpgrade((Game_Character*)e->obj);
		forceDie();
	}
}

void Obj_UpgradeBase::Render()
{
	Game_ObjectBase::Render();
}
int Obj_UpgradeBase::getSFXexplodeID()
{
	return 22;
}
