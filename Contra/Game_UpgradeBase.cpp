#include "Game_UpgradeBase.h"
#include "Game_DeadlyBlock.h"
#include "Game_Player.h"
#include "State_Contra_Jump.h"

Game_UpgradeBase::Game_UpgradeBase(float x, float y, int z, int width, int height) : Game_SpecialObject(x, y, z, width, height)
{
	_state.reset(new State_Contra_Jump(this));
	_ForceX = 64;
	_ForceY = _jumpHeight;

};
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
