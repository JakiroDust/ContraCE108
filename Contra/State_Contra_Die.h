#pragma once
#include "State_Contra_Base.h"
class State_Contra_Die : public State_Contra_Base
{
	private:
		int _delayDelete = 1;
		bool _trigger = true;
	public:
		State_Contra_Die(Game_ObjectBase* obj, int delayDelete) : State_Contra_Base(obj) { _delayDelete = delayDelete; }

		int StateId() override { return STATE_DIE; }

		void Render() override;
		void Update(DWORD dt) override;

};

