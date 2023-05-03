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