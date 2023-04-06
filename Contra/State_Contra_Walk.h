#pragma once

#include "State_Contra_Base.h"

class State_Contra_Walk : public State_Contra_Base
{
	private:
		bool left_release = false;
		bool right_release = false;
	public:
		State_Contra_Walk(Game_ObjectBase* obj) : State_Contra_Base(obj){}

		int StateId() override { return STATE_WALK; }
		void Render() override;
		void Update(DWORD dt) override;

		void KeyHold_Left() override;
		void KeyHold_Right() override;
		void KeyPressed_Jump() override;
		void KeyReleased_Left() override;
		void KeyReleased_Right() override;
};

