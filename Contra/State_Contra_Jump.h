#pragma once
#include "State_Contra_Base.h"

class State_Contra_Jump : public State_Contra_Base
{
	public:
		State_Contra_Jump(Game_ObjectBase* obj) : State_Contra_Base(obj) {}

		int StateId() override { return STATE_JUMP; }
		void Render() override;
		void Update(DWORD dt) override;

		void KeyHold_Left() override;
		void KeyHold_Right() override;
};

