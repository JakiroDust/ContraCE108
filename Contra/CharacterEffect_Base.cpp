#include "CharacterEffect_Base.h"
CharacterEffect_Base::CharacterEffect_Base(Game_Character* _target, int _duration,bool isInfinity)
{
	target = _target;
	duration = _duration;
	start();
	_isInfinity = isInfinity;
}
bool CharacterEffect_Base::isExpired()
{
	return _isExpired;
}

void CharacterEffect_Base::update(UWORD& dt)
{
	_apply_Duration(dt);
	_update_Duration(dt);
}
void CharacterEffect_Base::_update_Duration(UWORD& dt)
{
	if (!_isInfinity)
		return;
	duration -= dt;
	if (duration <= 0)
		forceExpire();
}

void CharacterEffect_Base::forceExpire()
{
	_remove_Effect();
	_isExpired = true;

}


void CharacterEffect_Base::start()
{
}

void CharacterEffect_Base::_apply_Duration(UWORD& dt)
{
}

void CharacterEffect_Base::_remove_Effect()
{
}




