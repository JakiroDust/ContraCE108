#pragma once
#include "State_Contra_Base.h"

class State_Station : public State_Contra_Base
{
	public:
		State_Station(Game_ObjectBase* obj) : State_Contra_Base(obj) {}
		int StateId() override { return STATE_WALK; }
		void Render() override;
		void Update(DWORD dt) override;

		void KeyPressed_Left() override;
		void KeyPressed_Right() override;
		void KeyPressed_Jump() override;
		void KeyPressed_Shoot() override;
};

