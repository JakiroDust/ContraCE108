#pragma once
#include "State_Turret_Base.h"

class State_Turret_Active : public State_Turret_Base
{
	private:
		int _currentAngle = 1;
		
		void Rotate_Clockwise()
		{
			if (_currentAngle < DIR_12_OCLOCK)
				_currentAngle++;
			else
				_currentAngle = 1;
		}
		void Rotate_Counterclockwise()
		{
			if (_currentAngle > DIR_1_OCLOCK)
				_currentAngle--;
			else
				_currentAngle = DIR_12_OCLOCK;
		}
	public:
		State_Turret_Active(Game_ObjectBase* obj, int angle = DIR_12_OCLOCK) : State_Turret_Base(obj)
		{
			_currentAngle = angle;
		}
		int StateId() override { return STATE_EMERGE; }
		void Render() override;
		void Update(DWORD dt) override;

		int CurrentAngle() { return _currentAngle; }

		void SetAngle(int angle)
		{
			if (angle < 1 && angle > 12)
				_currentAngle = 12;
			else
				_currentAngle = angle;
		}

		virtual void KeyPressed_Left() override { Rotate_Clockwise(); }
		virtual void KeyPressed_Right() override { Rotate_Counterclockwise(); }
		virtual void KeyPressed_Shoot() override;
		virtual void KeyPressed_Hide() override;
};

