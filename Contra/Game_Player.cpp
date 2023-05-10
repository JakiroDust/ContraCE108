#include "Game_Player.h"
#include "Game.h"
#include "State_Contra_Idle.h"
#include "State_Contra_Walk.h"
#include "State_Contra_Fall.h"
#include "State_Contra_Swim.h"
#include "State_Contra_Jump.h"
#include "Contra_GET_ANI.h"
#include "Enemy_RedGunner.h"

int Game_Player::CharID()
{
	return CHAR_CONTRA;
}

void Game_Player::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_Character::Update(dt, coObjects);
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
		_state.reset(new State_Contra_Idle(this));
		return;
	}

	switch (_state->NextState())
	{
		
	case STATE_IDLE:
		
		_state.reset( new State_Contra_Idle(this));
		break;
	case STATE_WALK:
		
		_state.reset(new State_Contra_Walk(this));
		break;
	case STATE_FALL:
		
		_state.reset(new State_Contra_Fall(this));
		break;
	case STATE_SWIM:
		
		_state.reset(new State_Contra_Swim(this));
		break;
	case STATE_JUMP:
		
		_state.reset(new State_Contra_Jump(this));
		break;
	}
}

void Game_Player::KeyDownEventHandler(int KeyCode)
{
	if (_state.get() == NULL)
		return;

	// Player characer in force-moving state, ignore KeyEvent.
	if (_ForceX != 0)
		return;
	
	State_Contra_Base* state = (State_Contra_Base*)_state.get();
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
	if (_state.get() == NULL || !_auto)
		return;

	State_Contra_Base* state = (State_Contra_Base*)_state.get();

	switch (KeyCode)
	{
	case DIK_UP:
		state->KeyReleased_Up();
		break;
	case DIK_DOWN:
		state->KeyReleased_Down();
		break;
	case DIK_LEFT:
		state->KeyReleased_Left();
		break;
	case DIK_RIGHT:
		state->KeyReleased_Right();
		break;
	case DIK_O:
		state->KeyReleased_Shoot();
		break;
	case DIK_P:
		state->KeyReleased_Jump();
		break;
	}
}

void Game_Player::KeyReleaseAll()
{
	KeyUpEventHandler(DIK_UP);
	KeyUpEventHandler(DIK_DOWN);
	KeyUpEventHandler(DIK_LEFT);
	KeyUpEventHandler(DIK_RIGHT);
	KeyUpEventHandler(DIK_O);
	KeyUpEventHandler(DIK_P);
}

void Game_Player::KeyStateHandler(BYTE* state)
{
	if (_state == NULL)
		return;

	// Player characer in force-moving state, ignore KeyEvent.
	if (_ForceX != 0)
		return;
	
	LPGAME game = CGame::GetInstance();
	State_Contra_Base* CharState = (State_Contra_Base*)_state.get();
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

	if (game->IsKeyDown(DIK_O))
	{
		CharState->KeyHold_Shoot();
	}
	else
	{
		CharState->KeyReleased_Shoot();
	}
}

void Game_Player::OnNoCollision(DWORD dt) 
{
	Game_Character::OnNoCollision(dt);
}

void Game_Player::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_Character::OnCollisionWith(e);
	if (dynamic_cast<Enemy_RedGunner*>(e->obj))
	{
		Game_Character* enemy = (Game_Character*)(e->obj);
		enemy->forceDie();
	}
}

void Game_Player::GetCustomSize(int state, int& width, int& height)
{
	switch (state)
	{
	case STATE_IDLE:
		width = PLAYER_BASE_WIDTH;
		height = PLAYER_BASE_HEIGHT;
		break;
	case STATE_FALL:
		width = PLAYER_BASE_WIDTH;
		height = PLAYER_BASE_HEIGHT;
		break;
	case STATE_SWIM:
		width = PLAYER_SWIM_WIDTH;
		height = PLAYER_SWIM_HEIGHT;
		break;
	case STATE_WALK:
		width = PLAYER_BASE_WIDTH;
		height = PLAYER_BASE_HEIGHT;
		break;
	case STATE_JUMP:
		width = PLAYER_JUMP_WIDTH;
		height = PLAYER_JUMP_HEIGHT;
		break;
	case STATE_DIE:
		width = PLAYER_BASE_WIDTH;
		height = PLAYER_BASE_HEIGHT;
		break;
	default:
		break;
	}
}