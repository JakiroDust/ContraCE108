#include "Game_Effect.h"

void Game_Effect::Update(DWORD dt)
{
	Game_StaticObject::Update(dt);
	if (atFinalFrame())
	{
		DeleteThis();
	}
}

void Game_Effect::Render()
{
	if (_isDeleted)
		return;
	Game_StaticObject::Render();
}