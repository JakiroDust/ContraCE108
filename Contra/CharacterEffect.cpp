#include "CharacterEffect.h"
#include "Game_Player.h"
CharacterEffect_Barrier::CharacterEffect_Barrier(Game_Character* _target, int _duration, bool isInfinity) :CharacterEffect_Base(_target,_duration,isInfinity)
{
}
void CharacterEffect_Barrier::start()
{
	if (dynamic_cast<Game_Player*>(target))
	{
		Game_Player* ptr = (Game_Player*)target;
		ptr->Apply_UpgradeB();
	}
}
