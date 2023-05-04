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