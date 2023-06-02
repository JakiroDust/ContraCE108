#include "Game_UpgradeBase.h"
#include "Game_DeadlyBlock.h"
#include "Game_Player.h"
void Game_UpgradeBase::OnCollisionWith(PCOLLISIONEVENT e)
{
	if (e->obj->IsDeleted())
		return;

	Game_Character::OnCollisionWith(e);

	// Collision with deadly block
	if (dynamic_cast<Game_DeadlyBlock*>(e->obj))
	{
		DeleteThis();
		return;
	}
	if (dynamic_cast<Game_Player*>(e->obj))
	{
		applyUpgrade();
		DeleteThis();
		return;
	}
}

void Game_UpgradeBase::Render()
{
	_Render(_SpriteId);
}
