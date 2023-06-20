#include "Game_Effect.h"
#include "MusicManager.h"
void Game_Effect::Update(DWORD dt)
{
	Game_StaticObject::Update(dt);

	if (_DelayTick > dt)
	{
		_DelayTick -= dt;
		return;
	}
	else if (_DelayTick > 0)
	{
		SoundSystem::getInstance()->playSFX(_startSFX, CHANNEL_SFX_ENV, 0);
		_DelayTick = 0;
	}

	if (atFinalFrame(_SpriteId))
	{
		DeleteThis();
	}
}

void Game_Effect::Render()
{
	if (_isDeleted || _DelayTick > 0)
		return;
	Game_StaticObject::Render();
}

