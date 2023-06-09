#include "Enemy_AlienBase_HandCell.h"
#include "Enemy_AlienBase_Body.h"
#include "Scene_Battle.h"
#include "GameManager.h"

#define DEGREE_TO_RAD 0.0174533f

int Enemy_AlienBase_HandCell::CharID()
{
	return ALIEN_BASE_HANDCELL;
}

int Enemy_AlienBase_HandCell_Main::CharID()
{
	return ALIEN_BASE_HANDCELL_MAIN;
}

void Enemy_AlienBase_HandCell::Update(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	Game_SpecialObject::Update(dt, coObjects);
}

void Enemy_AlienBase_HandCell::UpdateState()
{
	Game_SpecialObject::UpdateState();
}

void Enemy_AlienBase_HandCell::Render()
{
	if (_WaitForInit > 0)
		return;
	Game_SpecialObject::Render();
}

void Enemy_AlienBase_HandCell_Main::Execute_DieAction()
{
	Enemy_AlienBase_HandCell::Execute_DieAction();
	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Enemy_AlienBase_Body* body = (Enemy_AlienBase_Body*)(scene->getObjectByID(_bodyID));
	if (_isLeftHand)
		body->Kill_LeftHand();
	else
		body->Kill_RightHand();
}

void Enemy_AlienBase_HandCell::Execute_BeforeDelete()
{
	if (_die)
	{
		CreateDieAnimation(ANI_EXPLOSION_BULLET);
	}
}

void Enemy_AlienBase_HandCell::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	if (_die)
		return; 

	if (_WaitForInit > dt)
	{
		_WaitForInit -= dt;
		return;
	}
	else if (_WaitForInit > 0)
	{
		_WaitForInit = 0;
	}


	if (_ABC_ActionQueue.size() == 0)
	{
		return;
	}

	if (_ForceX != 0 || _ForceY != 0)
		return;

	ABCell_Action action = _ABC_ActionQueue[0];
	bool changePosFlag = false;

	switch (action.typeID)
	{
		case ABC_ACT_WAIT: 
		{
			if (action.value > dt)
				_ABC_ActionQueue[0].value -= dt;
			else
				_ABC_ActionQueue.erase(_ABC_ActionQueue.begin());
			return;
		}

		case ABC_ACT_MOVE_TO_REAR:
		{
			_currentDegree = action.value;
			// caculate dest position
			float x, y;
			x = cos(_currentDegree * DEGREE_TO_RAD) * _radius;
			y = sin(_currentDegree * DEGREE_TO_RAD) * _radius;
			_ForceX = x;
			_ForceY = y;
			_ABC_ActionQueue.erase(_ABC_ActionQueue.begin());
			break;
		}

		case ABC_ACT_MOVE_CLOCKWISE:
		{
			changePosFlag = true;
			float offset = _currentDegree < action.value ? -360 : 0;
			if ((_currentDegree >= action.value + offset && _currentDegree - AB_HANDCELL_RAD_SPEED <= action.value + offset)
				|| abs(_currentDegree - action.value - offset) < 1.0f)
			{
				_currentDegree = action.value;
				_ABC_ActionQueue.erase(_ABC_ActionQueue.begin());
			}
			else
			{
				_currentDegree -= AB_HANDCELL_RAD_SPEED;				
			}
			break;
		}

		case ABC_ACT_MOVE_COUNTERCLOCKWISE:
		{
			changePosFlag = true;
			float offset = _currentDegree > action.value ? 360 : 0;
			if ((_currentDegree <= action.value + offset && _currentDegree + AB_HANDCELL_RAD_SPEED >= action.value + offset)
				|| abs(_currentDegree - action.value - offset) < 1.0f)
			{
				_currentDegree = action.value;
				_ABC_ActionQueue.erase(_ABC_ActionQueue.begin());
			}
			else
			{
				_currentDegree += AB_HANDCELL_RAD_SPEED;
			}
			break;
		}

		case ABC_ACT_MOVE_CLOCK_AUTO:
		{
			float CounterclockwiseDistance = action.value - _currentDegree;
			CounterclockwiseDistance = CounterclockwiseDistance < 0 ? 360 + CounterclockwiseDistance : CounterclockwiseDistance;
			if (CounterclockwiseDistance > 180)
			{
				_ABC_ActionQueue[0].typeID = ABC_ACT_MOVE_CLOCKWISE;
			}
			else
			{
				_ABC_ActionQueue[0].typeID = ABC_ACT_MOVE_COUNTERCLOCKWISE;
			}
			return;
		}
	}

	// Fix degree value
	if (_currentDegree < 0)
	{
		_currentDegree = 360 - fmod(_currentDegree, -360);
	}
	else if (_currentDegree > 360)
	{
		_currentDegree = fmod(_currentDegree, 360);
	}

	if (changePosFlag)
	{
		float x, y;
		x = cosf(_currentDegree * DEGREE_TO_RAD) * _radius;
		y = sinf(_currentDegree * DEGREE_TO_RAD) * _radius;
		teleport(_centerX + x, _centerY + y);
	}
}

