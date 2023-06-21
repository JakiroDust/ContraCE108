#include "Enemy_AlienBase_Head.h"
#include "GameManager.h"
#include "MusicManager.h"
int Enemy_AlienBase_Head::CharID()
{
	return ALIEN_BASE_HEAD;
}

void Enemy_AlienBase_Head::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_SpecialObject::Update(dt, coObjects);
	if (GameManager::GetInstance()->Get_StagePasscardRemain() > 1)
		_immortal = true;
	else
		_immortal = false;
}

int Enemy_AlienBase_Head::getSFXexplodeID()
{
	return SFX_MAJOR_EXPLODE;
}

void Enemy_AlienBase_Head::Execute_DieAction()
{
	Game_SpecialObject::Execute_DieAction();
	GameManager::GetInstance()->Gain_StagePasscard();
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Enemy_AlienBase_Body* body = (Enemy_AlienBase_Body*)(scene->getObjectByID(_BodyID));
	body->Kill_LeftHand();
	body->Kill_RightHand();
}

void Enemy_AlienBase_Head::Execute_BeforeDelete()
{
	if (_die)
	{
		CreateDieAnimation(ANI_EXPLOSION_CONSTRUCT);
	}
}