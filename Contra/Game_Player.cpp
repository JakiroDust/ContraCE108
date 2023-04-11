#include "Game_Player.h"
#include "Game.h"
#include "State_Contra_Idle.h"
#include "State_Contra_Walk.h"
#include "State_Contra_Fall.h"
#include "State_Contra_Swim.h"
#include "State_Contra_Jump.h"
#include "Contra_GET_ANI.h"

int Game_Player::CharID()
{
	return CHAR_CONTRA;
}

void Game_Player::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_MovableObject::Update(dt, coObjects);
	Game_Collision::GetInstance()->Process(this, dt, coObjects);
	
	if (_state != NULL)
		_state->Update(dt);
	UpdateState();

	ResetStateParams();
}

void Game_Player::Render()
{
	RenderHitbox();
	if (_state != NULL)
		_state->Render();
}

void Game_Player::UpdateState()
{
	if (_state == NULL)
	{
		_state = new State_Contra_Idle(this);
		return;
	}

	switch (_state->NextState())
	{
	case STATE_IDLE:
		_state = new State_Contra_Idle(this);
		break;
	case STATE_WALK:
		_state = new State_Contra_Walk(this);
		break;
	case STATE_FALL:
		_state = new State_Contra_Fall(this);
		break;
	case STATE_SWIM:
		_state = new State_Contra_Swim(this);
		break;
	case STATE_JUMP:
		_state = new State_Contra_Jump(this);
		break;
	}
}

void Game_Player::KeyDownEventHandler(int KeyCode)
{
	if (_state == NULL)
		return;

	// Player characer in force-moving state, ignore KeyEvent.
	if (_ForceX != 0)
		return;
	
	State_Contra_Base* state = (State_Contra_Base*)_state;
	switch (KeyCode)
	{
	case DIK_UP:
		state->KeyPressed_Up();
		break;
	case DIK_DOWN:
		state->KeyPressed_Down();
		break;
	case DIK_LEFT:
		state->KeyPressed_Left();
		break;
	case DIK_RIGHT:
		state->KeyPressed_Right();
		break;
	case DIK_O: 
		state->KeyPressed_Shoot();
		break;
	case DIK_P:
		state->KeyPressed_Jump();
		break;
	}
}

void Game_Player::KeyUpEventHandler(int KeyCode)
{
	//if (_state == NULL)
	//	return;

	//State_Contra_Base* state = (State_Contra_Base*)_state;

	//switch (KeyCode)
	//{
	//case DIK_UP:
	//	state->KeyReleased_Up();
	//	break;
	//case DIK_DOWN:
	//	state->KeyReleased_Down();
	//	break;
	//case DIK_LEFT:
	//	state->KeyReleased_Left();
	//	break;
	//case DIK_RIGHT:
	//	state->KeyReleased_Right();
	//	break;
	//case DIK_O:
	//	state->KeyReleased_Shoot();
	//	break;
	//case DIK_P:
	//	state->KeyReleased_Jump();
	//	break;
	//}
}

void Game_Player::KeyStateHandler(BYTE* state)
{
	if (_state == NULL)
		return;

	// Player characer in force-moving state, ignore KeyEvent.
	if (_ForceX != 0)
		return;
	
	LPGAME game = CGame::GetInstance();
	State_Contra_Base* CharState = (State_Contra_Base*)_state;
	if (game->IsKeyDown(DIK_UP))
	{
		CharState->KeyHold_Up();
		CharState->KeyReleased_Down();
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		CharState->KeyHold_Down();
		CharState->KeyReleased_Up();
	}
	else
	{
		CharState->KeyReleased_Down();
		CharState->KeyReleased_Up();
	}

	if (game->IsKeyDown(DIK_RIGHT))
	{
		CharState->KeyHold_Right();
		CharState->KeyReleased_Left();
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		CharState->KeyHold_Left();
		CharState->KeyReleased_Right();
	}
	else
	{
		CharState->KeyReleased_Left();
		CharState->KeyReleased_Right();
	}
}

void Game_Player::OnNoCollision(DWORD dt) 
{
	Game_Character::OnNoCollision(dt);
}

void Game_Player::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_Character::OnCollisionWith(e);
}
