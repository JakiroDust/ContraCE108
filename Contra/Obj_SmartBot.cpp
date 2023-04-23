#include "Obj_SmartBot.h"
#include "Game_Platform.h"
#include "Game_Blocker.h"
#include "Contra_GET_ANI.h"
#include "Game_TestBox.h"
#include "Scene_Battle.h"
#include "Spatial.h"
#include "State_Contra_Base.h"
#include "Game_Player.h"

int Obj_SmartBot::CharID()
{
	return CHAR_CONTRA;
}

void Obj_SmartBot::UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects)
{
	// HAVE OTHER ACTION IN QUEUE
	if (_ActionQueue.size() != 0)
		return;

	// IN FORCE
	if (_ForceX != 0)
		return;

	// Use Game_TestBox to check surround environment
	// before making decision on what to do next.
	unique_ptr<Game_TestBox> testbox (new Game_TestBox(_x,_y,_z,_width,_height,0,0));

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());
	Game_Player* player = scene->p1();


	bool FACE_LEFT = false;
	if (footerX() >= player->footerX())
		FACE_LEFT = true;

	// THIS BOT IS CLOSED TO PLAYER
	if (abs(testbox->footerX() - player->footerX()) < 0.5
		&& abs(testbox->footerY() - player->footerY()) < 0.5)
	{

		
		return;
	}

	// define some params
	float NEAR_X = _moveSpd * dt * 2;
	float NEAR_Y = JUMP_VECTOR * dt * 2;

	 //Get all Collision objects. 
	vector<int> colList = (scene->spatial->getNearByIDyx(_y, _x));
	vector<Game_ObjectBase*>* collisionObjects = scene->getObjectById(colList);

	// Update Map
	
	// Map update incorrectly when dt dropping. Not use below code for now
	//_map->SetDt(dt);
	if (_map->UpdateMap(collisionObjects))
	{
		_path.clear();
	}

	//_map->UpdateMap(collisionObjects);
	collisionObjects->clear();
	delete collisionObjects;
	PTERRAINNODE desNode = _map->GetDesNode(player);

	if (_map->GetHome() == NULL)
	{
		
		return;
	}

	if (desNode == NULL)
	{
		
		return;
	}

	// Check if need update path or not
	if (!_path.empty() && 
		desNode->obj != _path[_path.size() - 1]->obj) // if target change TNode
	{
		_path.clear();
		_path = _map->FindWay(player);
	}
	else if (!_path.empty() && _map->GetHome()->obj != _path[0]->obj)
	{
		_path.clear();
		_path = _map->FindWay(player);
	}
	else if (_path.empty()) // not have path yet
	{
		_path.clear();
		_path = _map->FindWay(player);
	}


	// TEST Y POSITION
	// Target and this bot on same terrain
	if (_path.size() == 1)
	{	
		if (abs(footerX() - player->footerX()) > NEAR_X)
			if (FACE_LEFT)
				AddAction(DIK_LEFT);
			else
				AddAction(DIK_RIGHT);
	}
	// Target and this bot on different terrains (above or same height)
	else if(_path.size() > 1)
	{
		Game_Terrain* currentT = _path[0]->obj;
		Game_Terrain* nextT = _path[1]->obj;

		// Detect update incorrectly
		if (_map->GetHome()->obj == nextT)
		{
			
			return;
		}

		pair<float, float> NextT_Cost = _path[0]->nextNodes[nextT->id()];

		bool NEED_JUMP = !dynamic_cast<Game_Water*>(currentT) && NextT_Cost.second < 0;
		bool NEED_JUMPDOWN = NextT_Cost.second > 0;

		if (footerX() >= nextT->x() + nextT->width() / 2.0f)
			FACE_LEFT = true;
		else
			FACE_LEFT = false;

		if (!NEED_JUMP)
		{
			// nextT below
			if (NEED_JUMPDOWN && dynamic_cast<Game_Platform*>(currentT) &&
				footerX() >= nextT->x() && footerX() <= nextT->x() + nextT->width())
			{
				AddAction(-1);
				AddAction(DIK_DOWN, DIK_P);
				
				return;
			}
			else if (NEED_JUMPDOWN &&
					(footerX() < nextT->x()
						|| footerX() > nextT->x() + nextT->width()
						|| abs(currentT->x() + currentT->width() - nextT->x()) < 0.5
						|| abs(nextT->x() + nextT->width() - currentT->x()) < 0.5))
			{
				if (footerX() < nextT->x() + nextT->width() / 2)
					AddAction(DIK_RIGHT);
				else
					AddAction(DIK_LEFT);
				
				return;
			}
			else if (NEED_JUMPDOWN
					&&	NextT_Cost.first != 0)
			{
				// bot is near border of terrain
				if ((footerX() - NEAR_X < currentT->x())
					|| (footerX() + NEAR_X > currentT->x() + currentT->width()))
				{
					if (FACE_LEFT)
					{
						AddAction(DIK_P, DIK_LEFT);
						AddAction(DIK_LEFT);
						for (float i = -1; i < (abs(NextT_Cost.first) / (_moveSpd * dt)) ; i++)
						{
							AddAction(DIK_LEFT);
						}
					}
					else
					{
						AddAction(DIK_P, DIK_RIGHT);
						AddAction(DIK_RIGHT);
						for (float i = -1; i < (abs(NextT_Cost.first) / (_moveSpd * dt)); i++)
						{
							AddAction(DIK_RIGHT);
						}
					}
					
					return;
				}
			}
			else if (NEED_JUMPDOWN &&
				footerX() < nextT->x() || footerX() > nextT->x() + nextT->width())
			{
				if (footerX() < nextT->x())
					AddAction(DIK_RIGHT);
				else
					 AddAction(DIK_LEFT) ;
			}

			if (footerX() < nextT->x() + NEAR_X)
				AddAction(DIK_RIGHT);
			else
				AddAction(DIK_LEFT);
			
			return;
		} 
		// NEED JUMP
		else
		{
			// nextT above
			if (footerX() > nextT->x() && footerX() < nextT->x() + nextT->width()
				&& abs(footerX() - nextT->x()) > 1 && abs(footerX() - (nextT->x() + nextT->width())) > 1)
			{
				AddAction(DIK_P);
				
				return;
			}

			// NextT above and not intersect X 
			if (NextT_Cost.first != 0 || abs(currentT->x() + currentT->width() - nextT->x()) < 0.5
					|| abs(nextT->x() + nextT->width() - currentT->x()) < 0.5)
			{
				// bot is near border of terrain
				if ((footerX() < currentT->x())
					|| (footerX() > currentT->x() + currentT->width()))
				{
					if (FACE_LEFT)
					{
						AddAction(DIK_P, DIK_LEFT);
						AddAction(DIK_LEFT);
						for (float i = -1; i < (abs(NextT_Cost.first) / (_moveSpd * dt)); i++)
						{
							AddAction(DIK_LEFT);
						}
					}
					else
					{
						AddAction(DIK_P, DIK_RIGHT);
						AddAction(DIK_RIGHT);
						for (float i = -1; i < (abs(NextT_Cost.first) / (_moveSpd * dt)); i++)
						{
							AddAction(DIK_RIGHT);
						}
					}
					
					return;
				}
				// still in terrain
				else if ((footerX() > currentT->x())
					|| (footerX() < currentT->x() + currentT->width()))
				{
					if (abs(footerX() - (nextT->x() + nextT->width() / 2.0f)) > 0.5)
						if (FACE_LEFT)
							AddAction(DIK_LEFT);
						else
							AddAction(DIK_RIGHT);
					
					return;
				}
			}
		}	
	}
	//// player is under this bot
	//else if (testbox->footerY() - player->footerY() < -_width)
	//{
	//	Game_Terrain* currentT = _map->GetHome()->obj;

	//	// obj is near border of terrain
	//	if ((footerX() - NEAR_X < currentT->x() && FACE_LEFT)
	//		|| (footerX() + NEAR_X > currentT->x() + currentT->width() && !FACE_LEFT))
	//	{
	//		// Jump down
	//		if (abs(footerX() - player->footerX()) < NEAR_X)
	//		{
	//			AddAction(-1);
	//			AddAction(DIK_DOWN);
	//			AddAction(DIK_P);
	//			return;
	//		}

	//		// Jump off platform.
	//		AddAction(-1);
	//		if (FACE_LEFT)
	//			AddAction(DIK_P, DIK_LEFT);
	//		else
	//			AddAction(DIK_P, DIK_RIGHT);
	//		return;
	//	}

	//	// Not near border of terrain

	//	// Near player by X
	//	if (abs(footerX() - player->footerX()) < NEAR_X)
	//	{
	//		// jump down
	//		AddAction(-1);
	//		AddAction(DIK_DOWN);
	//		AddAction(DIK_P);
	//		return;
	//	}
	//	else
	//	{
	//		// Continue moving to near player.
	//		if (FACE_LEFT)
	//			AddAction(DIK_LEFT);
	//		else
	//			AddAction(DIK_RIGHT);
	//		return;
	//	}

	//	if (abs(footerX() - player->footerX()) > NEAR_X)
	//		if (FACE_LEFT)
	//			AddAction(DIK_LEFT);
	//		else
	//			AddAction(DIK_RIGHT);
	//	return;
	//}

	
	// DELETE POINTER
	
}

void Obj_SmartBot::OnNoCollision(DWORD dt)
{
	Game_Enemy::OnNoCollision(dt);
}

void Obj_SmartBot::OnCollisionWith(PCOLLISIONEVENT e)
{
	Game_Enemy::OnCollisionWith(e);
}

void Obj_SmartBot::GetCustomSize(int state, int& width, int& height)
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