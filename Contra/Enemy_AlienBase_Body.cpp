#include "Enemy_AlienBase_Body.h"
#include "State_Object_Hide.h"
#include "ScreenManager.h"
#include "Enemy_AlienBase_HandCell.h"
#include "GameManager.h"

#define RAD_TO_DEG 57.29578f

Enemy_AlienBase_Body::Enemy_AlienBase_Body(float x, float y, int z) : Game_SpecialObject(x, y, z, ALIENBASE_WIDTH, ALIENBASE_HEIGHT)
{
	_moveSpd = 0;
	_haveStandby = false;
	_BodyDamage = false;
	_faceLeft = true;
	_ghost = true;
	_gravity = false;
}

int Enemy_AlienBase_Body::CharID()
{
	return ALIEN_BASE;
}

void Enemy_AlienBase_Body::UpdateState()
{
	// begin with hide state
	if (_state == NULL)
		_state.reset(new State_Object_Hide(this));
	Game_SpecialObject::UpdateState();
}

void Enemy_AlienBase_Body::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_SpecialObject::Update(dt, coObjects);

	if (!_start && GameManager::GetInstance()->Get_StagePasscardRemain() <= 1)
	{
		_start = true;
	}
}

void Enemy_AlienBase_Body::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	// Init
	if (!_start)
	{
		return;
	}
	else if (_state->StateId() == STATE_OBJ_HIDE)
	{
		AddAction(DIK_O);
		return;
	}
	else if (!_init)
	{
		_init = true;
		Act_Init();
		return;
	}

	// Shooting



	// Both hands die, no need to run code below
	if (_leftHand_Die && _rightHand_Die)
		return;

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	
	// Check if all parts finish its action or not
	if (!CheckParts_IsIdle())
	{
		return;
	}
	else
	{
		if (_currentActionIndex < _MoveSet.size() - 1)
		{
			_currentActionIndex++;
		}
		else
		{
			_currentActionIndex = 0;
		}
	}

	// perform action
	switch (_MoveSet[_currentActionIndex])
	{
		case AB_ACT_WAVING:
		{
			Act_Waving();
			break;
		}
		case AB_ACT_SPINNING:
		{
			Act_Spinning();
			break;
		}
		case AB_ACT_COVERING:
		{
			Act_Covering();
			break;
		}
		case AB_ACT_AIMING:
		{
			Act_Aiming();
			break;
		}
	}

}

bool Enemy_AlienBase_Body::CheckParts_IsIdle()
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	bool idle = true;
	// check left hand first
	for (int i = 0; i < 5; i++)
	{
		Enemy_AlienBase_HandCell* part = (Enemy_AlienBase_HandCell*)(scene->getObjectByID(_leftHand[i]));
		if (!part->ABC_IsIdle())
		{
			idle = false;
			break;
		}
	}
	// check right hand
	if (idle)
	{
		for (int i = 0; i < 5; i++)
		{
			Enemy_AlienBase_HandCell* part = (Enemy_AlienBase_HandCell*)(scene->getObjectByID(_rightHand[i]));
			if (!part->ABC_IsIdle())
			{
				idle = false;
				break;
			}
		}
	}

	return idle;
}

void Enemy_AlienBase_Body::Kill_LeftHand()
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	for (int i = 0; i < 5; i++)
	{
		Game_Enemy* enemy = (Game_Enemy*)scene->getObjectByID(_leftHand[i]);
		enemy->forceDie();
	}
	_leftHand_Die = true;
}

void Enemy_AlienBase_Body::Kill_RightHand()
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	for (int i = 0; i < 5; i++)
	{
		Game_Enemy* enemy = (Game_Enemy*)scene->getObjectByID(_rightHand[i]);
		enemy->forceDie();
	}
	_rightHand_Die = true;
}

// BEHAVIOR

void Enemy_AlienBase_Body::Act_Init()
{
	float Lcx = 72, Lcy = 2060;
	float Rcx = 184, Rcy = 2060;
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	unique_ptr<Enemy_AlienBase_HandCell> part;
	unique_ptr<Enemy_AlienBase_HandCell_Main> mainpart;
	// left hand
	mainpart.reset(new Enemy_AlienBase_HandCell_Main(_x, _y, Z_INDEX_ENEMY, AB_HANDCELL_RADIUS_BASE, 0));
	mainpart.get()->SetCenterPoint(Lcx, Lcy);
	mainpart.get()->ABC_AddAction(ABC_ACT_MOVE_TO_REAR, 135);
	_leftHand[4] = scene->add_object(move(mainpart));
	for (int i = 3; i >= 0; i--)
	{
		part.reset(new Enemy_AlienBase_HandCell(_x, _y, Z_INDEX_ENEMY, AB_HANDCELL_RADIUS_BASE, (4-i) * AB_HANDCELL_WAIT_INIT_INTERVAL));
		part.get()->SetCenterPoint(Lcx, Lcy);
		part.get()->ABC_AddAction(ABC_ACT_MOVE_TO_REAR, 135);
		_leftHand[i] = scene->add_object(move(part));
	}


	// right hand
	mainpart.reset(new Enemy_AlienBase_HandCell_Main(_x, _y, Z_INDEX_ENEMY, AB_HANDCELL_RADIUS_BASE, 0));
	_rightHand[4] = scene->add_object(move(mainpart));
	for (int i = 3; i >= 0; i--)
	{
		part.reset(new Enemy_AlienBase_HandCell(_x, _y, Z_INDEX_ENEMY, AB_HANDCELL_RADIUS_BASE, (4 - i) * AB_HANDCELL_WAIT_INIT_INTERVAL));
		part.get()->SetCenterPoint(Rcx, Rcy);
		part.get()->ABC_AddAction(ABC_ACT_MOVE_TO_REAR, 45);
		_rightHand[i] = scene->add_object(move(part));
	}
}

void Enemy_AlienBase_Body::Act_Spinning()
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Enemy_AlienBase_HandCell* part;
	// Left hand
	if (!_leftHand_Die)
	{
		for (int i = 1; i < 4; i++)
		{
			part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_leftHand[i]);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 135);
			part->ABC_AddAction(ABC_ACT_WAIT, (i - 1) * AB_HANDCELL_PART_WAIT_INTERVAL);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 130);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 30);
		}
	}

	// Right Hand
	if (!_rightHand_Die)
	{
		for (int i = 1; i < 4; i++)
		{
			part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_rightHand[i]);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 45);
			part->ABC_AddAction(ABC_ACT_WAIT, (i - 1) * AB_HANDCELL_PART_WAIT_INTERVAL);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 40);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 150);
		}
	}
}

void Enemy_AlienBase_Body::Act_Waving()
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Enemy_AlienBase_HandCell* part;
	// Left hand
	if (!_leftHand_Die)
	{
		for (int i = 1; i < 4; i++)
		{
			part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_leftHand[i]);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 135);
			part->ABC_AddAction(ABC_ACT_WAIT, (i - 1) * AB_HANDCELL_PART_WAIT_INTERVAL);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 225);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 135);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 225);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 135);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 225);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 135);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 225);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 135);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 225);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 135);
		}
	}


	// Right Hand
	if (!_rightHand_Die)
	{
		for (int i = 1; i < 4; i++)
		{
			part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_rightHand[i]);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 45);
			part->ABC_AddAction(ABC_ACT_WAIT, (i - 1) * AB_HANDCELL_PART_WAIT_INTERVAL);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 315);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 45);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 315);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 45);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 315);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 45);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 315);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 45);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 315);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 45);
		}
	}
}

void Enemy_AlienBase_Body::Act_Aiming()
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Enemy_AlienBase_HandCell* part;

	// Left hand
	if (!_leftHand_Die)
	{
		// calc left angle
		float Lcx, Lcy;
		scene->getObjectByID(_leftHand[0])->GetCenterPoint(Lcx, Lcy);
		Game_Player* player = scene->p1();
		float adjacentL = player->x() - Lcx;
		float oppositeL = player->y() - Lcy;
		float hypotenuseL = sqrt(adjacentL * adjacentL + oppositeL * oppositeL);
		float angleL = 360 - roundf(acosf(oppositeL / hypotenuseL) * RAD_TO_DEG);

		// add action
		for (int i = 1; i < 4; i++)
		{
			part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_leftHand[i]);
			part->ABC_AddAction(ABC_ACT_WAIT, (i - 1) * AB_HANDCELL_PART_WAIT_INTERVAL);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCK_AUTO, angleL);
		}
	}

	// Right Hand
	if (!_rightHand_Die)
	{
		// calc right angle
		float Rcx, Rcy;
		scene->getObjectByID(_rightHand[0])->GetCenterPoint(Rcx, Rcy);
		Game_Player* player = scene->p1();
		float adjacentR = player->x() - Rcx;
		float oppositeR = player->y() - Rcy;
		float hypotenuseR = sqrt(adjacentR * adjacentR + oppositeR * oppositeR);
		float angleR = 360 - roundf(acosf(oppositeR / hypotenuseR) * RAD_TO_DEG);

		for (int i = 1; i < 4; i++)
		{
			part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_rightHand[i]);
			part->ABC_AddAction(ABC_ACT_WAIT, (i - 1) * AB_HANDCELL_PART_WAIT_INTERVAL);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCK_AUTO, angleR);
		}
	}
}

void Enemy_AlienBase_Body::Act_StandbyForAiming()
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Enemy_AlienBase_HandCell* part;
	// Left hand
	if (!_leftHand_Die)
	{
		for (int i = 1; i < 4; i++)
		{
			part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_leftHand[i]);
			part->ABC_AddAction(ABC_ACT_WAIT, (i - 1) * AB_HANDCELL_PART_WAIT_INTERVAL);
			part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 180);
		}
	}

	// Right Hand
	if (!_rightHand_Die)
	{
		for (int i = 1; i < 4; i++)
		{
			part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_rightHand[i]);
			part->ABC_AddAction(ABC_ACT_WAIT, (i - 1) * AB_HANDCELL_PART_WAIT_INTERVAL);
			part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 0);
		}
	}
}

void Enemy_AlienBase_Body::Act_Covering()
{
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Enemy_AlienBase_HandCell* part;
	// Left hand
	if (!_leftHand_Die)
	{
		// part 1
		part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_leftHand[1]);
		part->ABC_AddAction(ABC_ACT_WAIT, 0);
		part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 135);
		
		// part 2
		part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_leftHand[2]);
		part->ABC_AddAction(ABC_ACT_WAIT, AB_HANDCELL_PART_WAIT_INTERVAL);
		part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 145);

		// part 3
		part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_leftHand[3]);
		part->ABC_AddAction(ABC_ACT_WAIT, 2 * AB_HANDCELL_PART_WAIT_INTERVAL);
		part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 160);
	
		// part 4
		part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_leftHand[4]);
		part->ABC_AddAction(ABC_ACT_WAIT, 3 * AB_HANDCELL_PART_WAIT_INTERVAL);
		part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 180);
	}

	// Right Hand
	if (!_rightHand_Die)
	{
		// part 1
		part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_rightHand[1]);
		part->ABC_AddAction(ABC_ACT_WAIT, 0);
		part->ABC_AddAction(ABC_ACT_MOVE_CLOCKWISE, 45);

		// part 2
		part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_rightHand[2]);
		part->ABC_AddAction(ABC_ACT_WAIT, AB_HANDCELL_PART_WAIT_INTERVAL);
		part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 35);

		// part 3
		part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_rightHand[3]);
		part->ABC_AddAction(ABC_ACT_WAIT, 2 * AB_HANDCELL_PART_WAIT_INTERVAL);
		part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 15);

		// part 4
		part = (Enemy_AlienBase_HandCell*)scene->getObjectByID(_rightHand[4]);
		part->ABC_AddAction(ABC_ACT_WAIT, 3 * AB_HANDCELL_PART_WAIT_INTERVAL);
		part->ABC_AddAction(ABC_ACT_MOVE_COUNTERCLOCKWISE, 0);
	}
}

void Enemy_AlienBase_Body::Act_LeftHand_Shooting()
{

}

void Enemy_AlienBase_Body::Act_RightHand_Shooting()
{

}

void Enemy_AlienBase_Body::Act_Mouth_Shooting()
{

}