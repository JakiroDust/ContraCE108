#pragma once
#include "State_Contra_Base.h" 

class State_Contra_Idle : public State_Contra_Base
{
	private:
		bool HoldKeyDown = false;
	public:
		State_Contra_Idle(Game_ObjectBase* obj) : State_Contra_Base(obj) {}

		int StateId() override { return STATE_IDLE; }
		void Render() override;
		void Update(DWORD dt) override;

		void KeyHold_Left() override;
		void KeyHold_Right() override;
		void KeyHold_Down() override;
		void KeyReleased_Down() override;
		void KeyPressed_Jump() override;

};

