#include "Enemy_RedGunner.h"
#include "Contra_GET_ANI.h"
#include "Game_Water.h"
#include "Game_TestBox.h"
#include "Game_Player.h"
#include "Scene_Battle.h"
#include "State_Contra_Base.h"


int Enemy_RedGunner::CharID()
{
	return RED_GUNNER;
}

void Enemy_RedGunner::UpdateState()
{
	Game_MovableEnemy::UpdateState();
}

void Enemy_RedGunner::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_MovableEnemy::Update(dt, coObjects);
}

void Enemy_RedGunner::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_MovableEnemy::OnCollisionWith(e);
	if (dynamic_cast<Game_Water*>(e->obj))
	{
		DeleteThis();
		return;
	}
	if (dynamic_cast<Game_Bullet*>(e->obj))
	{
		Game_Bullet* bullet = ((Game_Bullet*)e->obj);
		if (bullet->OwnerID() == B_OWNER_PLAYER)
		{
			bullet->DeleteThis();
			forceDie();
			return;
		}
	}
}

void Enemy_RedGunner::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	AddAction(DIK_LEFT);
	
	//--------------------------------------------------------------------
	// Use testbox to check before making decision what to do next.
	unique_ptr<Game_TestBox>testbox(new Game_TestBox(_x, _y, _z, _width, _height, 0, 0));
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();

	// define some params
	float NEAR_X = _moveSpd * dt * 2;
	float NEAR_Y = JUMP_VECTOR * dt * 2;
	
	// Make testbox move down in order to get data of platform which this obj is standing on 
	testbox->SetSpeed(0, JUMP_VECTOR);
	testbox->Update(dt, coObjects);
	// Get Collisions and handle them.
	vector<PCOLLISIONEVENT>* coEvents = testbox->GetCollisionList();
	for (int i = 0; i < coEvents->size(); i++)
	{
		PCOLLISIONEVENT e = coEvents->at(i);
		// Check current terrain
		if (dynamic_cast<Game_Terrain*>(e->obj))
		{
			if (e->ny < 0)
			{
				// obj is near border of terrain
				if ((footerX() - NEAR_X < e->obj->x() &&  _faceLeft)
					|| (footerX() + NEAR_X > e->obj->x() + e->obj->width() && !_faceLeft))
				{
					// Perform jump
					if (_faceLeft)
						AddAction(DIK_P, DIK_LEFT);
					else
						AddAction(DIK_P, DIK_RIGHT);
					
					return;
				}
			}
		}
	}
	
}

void Enemy_RedGunner::Execute_DieAction()
{
	Game_MovableEnemy::Execute_DieAction();
	jump();
}

void Enemy_RedGunner::GetCustomSize(int state, int &width, int &height)
{
	switch (state)
	{
	case STATE_IDLE:
		width = REDGUNNER_BASE_WIDTH;
		height = REDGUNNER_BASE_HEIGHT;
		break;
	case STATE_FALL:
		width = REDGUNNER_BASE_WIDTH;
		height = REDGUNNER_BASE_HEIGHT;
		break;
	case STATE_SWIM:
		width = REDGUNNER_BASE_WIDTH;
		height = REDGUNNER_BASE_HEIGHT;
		break;
	case STATE_WALK:
		width = REDGUNNER_BASE_WIDTH;
		height = REDGUNNER_BASE_HEIGHT;
		break;
	case STATE_JUMP:
		width = REDGUNNER_JUMP_WIDTH;
		height = REDGUNNER_JUMP_HEIGHT;
		break;
	case STATE_DIE:
		width = REDGUNNER_BASE_WIDTH;
		height = REDGUNNER_BASE_HEIGHT;
		break;
	default:
		break;
	}
}