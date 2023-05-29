#pragma once
#include "State_Base.h"

#define STATE_OBJ_STANDBY 20
#define STATE_OBJ_ACTIVE 21
#define STATE_OBJ_HIDE 22
#define STATE_OBJ_EMERGE 23

class State_Object_Base : public State_Base
{
	public:
		State_Object_Base(Game_ObjectBase* obj) : State_Base(obj) {}

		int StateId() override { return -1; }
		void Render() override {}
		void Update(DWORD dt) override {}

		virtual void KeyPressed_Active() {}
		virtual void KeyPressed_Hide() {}
};

