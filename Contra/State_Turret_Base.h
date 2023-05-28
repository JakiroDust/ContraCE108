#pragma once
#include "State_Base.h"
#include "spawnBulletHelper.h"

// Turret && station
enum TurretState
{
	STATE_ACTIVE,
	STATE_EMERGE,
	STATE_HIDING,
	STATE_HIDE,
};

class State_Turret_Base : public State_Base
{
	protected:

	public:
		State_Turret_Base(Game_ObjectBase* obj) : State_Base(obj) {}
		virtual void KeyPressed_Left() {}
		virtual void KeyPressed_Right() {}
		virtual void KeyPressed_Shoot() {}
		virtual void KeyPressed_Hide() {}
};

