#include "Enemy_RedGunner.h"
#include "Contra_GET_ANI.h"
#include "Game_Water.h"
#include "Game_TestBox.h"
#include "Game_Player.h"
#include "Scene_Battle.h"

int Enemy_RedGunner::CharID()
{
	return CHAR_CONTRA;
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
	}
}

void Enemy_RedGunner::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	AddAction(DIK_LEFT);
	
	//--------------------------------------------------------------------
	// Use testbox to check before making decision what to do next.
	Game_TestBox* testbox = new Game_TestBox(_x, _y, _z, _width, _height, 0, 0);
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

