#include "Obj_BossAlienBase_S3.h"
#include "ScreenManager.h"
#include "GameManager.h"

void Obj_BossAlienBase_S3::Update(DWORD dt)
{
	if (!_explosionTrigger && GameManager::GetInstance()->Test_IfPassStage() == CAN_PASS_STAGE)
	{
		TriggerExplosion();
	}

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* p1 = scene->p1();

	if (_explosionTrigger)
	{
		if (_explosionTick > dt)
		{
			_explosionTick -= dt;
		}
		else if (!_finishExplosion)
		{
			StartExplosion();
		}
	}
}

void Obj_BossAlienBase_S3::Render()
{
	if (!_finishExplosion)
		RenderHitbox();
	else if (_SpriteId > 0)
	{
		CAnimations* animations = CAnimations::GetInstance();
		float x, y;
		GetCenterPoint(x, y);

		_Render(_SpriteId, x, y);
	}
}

void Obj_BossAlienBase_S3::StartExplosion()
{
	_finishExplosion = true;

	// animation
	Scene_Battle* scene = (Scene_Battle*)ScreenManager::GetInstance()->Scene();
	float x, y;
	GetCenterPoint(x, y);
	unique_ptr<Game_Effect> explosion1(new Game_Effect(x, y, Z_INDEX_ANIMATION, ANI_EXPLOSION_CONSTRUCT));
	scene->AddEffect(move(explosion1));
}

void Obj_BossAlienBase_S3::TriggerExplosion()
{
	_explosionTrigger = true;
	_explosionTick = BRIDGE_S1_EXPLOSION_INTERVAL + _explosionOffset;
}
