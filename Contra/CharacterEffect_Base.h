#pragma once
#include "Game_Character.h"
class CharacterEffect_Base
{
protected:
	Game_Character* target;
	int duration;
	bool _isInfinity;
	bool _isExpired=false;
	virtual void start();
	virtual void _update_Duration(UWORD& dt);
	virtual void _apply_Duration(UWORD& dt);
	virtual void _remove_Effect();
public:
	CharacterEffect_Base(Game_Character* _target, int _duration, bool isInfinity);
	virtual void update(UWORD& dt);
	virtual void forceExpire();
	bool isExpired();
};

