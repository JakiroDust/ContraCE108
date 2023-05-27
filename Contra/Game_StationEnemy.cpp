#include "Game_StationEnemy.h"
#include "State_Station.h"
#include "State_Station_Hide.h"
#include "State_Contra_Die.h"

void Game_StationEnemy::UpdateState()
{
	if (_state == NULL)
	{
		_state.reset(new State_Station(this));
		return;
	}

	if (_die && !dynamic_cast<State_Contra_Die*>(_state.get()))
	{
		_state.reset(new State_Contra_Die(this, 20));
		return;
	}
	else if (_die && dynamic_cast<State_Contra_Die*>(_state.get()))
	{
		return;
	}


	switch (_state->NextState())
	{

	case STATE_IDLE:
		_state.reset(new State_Station_Hide(this));
		break;
	case STATE_WALK:
		_state.reset(new State_Station(this));
		break;
	}
}

void Game_StationEnemy::KeyDownEventHandler(int KeyCode)
{
	Game_Enemy::KeyDownEventHandler(KeyCode);

	if (_state == NULL)
		return;

	// Characer in force-moving state, ignore KeyEvent.
	if (_ForceX != 0)
		return;

	if (dynamic_cast<State_Station*>(_state.get()))
	{
		State_Station* state = (State_Station*)_state.get();
		switch (KeyCode)
		{
		case DIK_NUMPAD1:
			state->KeyPressed_FaceDownLeft();
			break;
		case DIK_NUMPAD2:
			state->KeyPressed_FaceDown();
			break;
		case DIK_NUMPAD3:
			state->KeyPressed_FaceDownRight();
			break;
		case DIK_NUMPAD4:
			state->KeyPressed_FaceLeft();
			break;
		case DIK_NUMPAD6:
			state->KeyPressed_FaceRight();
			break;
		case DIK_NUMPAD7:
			state->KeyPressed_FaceUpLeft();
			break;
		case DIK_NUMPAD8:
			state->KeyPressed_FaceUp();
			break;
		case DIK_NUMPAD9:
			state->KeyPressed_FaceUpRight();
			break;
		}
	}
}

#define SLOPE_D1 0.41421f
#define SLOPE_D2 2.41421f
#define SLOPE_D3 -2.41421f
#define SLOPE_D4 -0.41421f
int Game_StationEnemy::Detect_Dir(float baseX, float baseY, float tarX, float tarY)
{
	// Find a, b of straight line formula (y = ax + b) ; (baseX, baseY) is a point on the line
	// a = slope
	// straight line formula: y = a(x - baseX) + baseY 
	// => b = baseY - a * baseX

	// d1 (angle inclination = 22.5 degree)
	float d1_a = SLOPE_D1;
	float d1_b = baseY - d1_a * baseX;
	// d2 (angle inclination = 67.5 degree)
	float d2_a = SLOPE_D2;
	float d2_b = baseY - d2_a * baseX;
	// d3 (angle inclination = 112.5 degree)
	float d3_a = SLOPE_D3;
	float d3_b = baseY - d3_a * baseX;
	// d4 (angle inclination = 157.5 degree)
	float d4_a = SLOPE_D4;
	float d4_b = baseY - d4_a * baseX;

	// above d1, below d4
	if (tarY > d1_a * tarX + d1_b && tarY < d4_a * tarX + d4_b)  return DIR_LEFT;
	// above d4, below d1
	else if (tarY > d4_a * tarX + d4_b && tarY < d1_a * tarX + d1_b)  return DIR_RIGHT;
	// above d2, above d3
	else if (tarY > d2_a * tarX + d2_b && tarY > d3_a * tarX + d3_b)  return DIR_TOP;
	// below d2, below d3
	else if (tarY < d2_a * tarX + d2_b && tarY < d3_a * tarX + d3_b)  return DIR_BOTTOM;
	// below d3, above d4
	else if (tarY < d3_a * tarX + d3_b && tarY > d4_a * tarX + d4_b)  return DIR_TOP_LEFT;
	// below d2, above d1
	else if (tarY < d2_a * tarX + d2_b && tarY > d1_a * tarX + d1_b)  return DIR_TOP_RIGHT;
	// below d1, above d2
	else if (tarY < d1_a * tarX + d1_b && tarY > d2_a * tarX + d2_b)  return DIR_BOTTOM_LEFT;
	// below d4, above d3
	else if (tarY < d4_a * tarX + d4_b && tarY > d3_a * tarX + d3_b)  return DIR_BOTTOM_RIGHT;
	else return -1;
}