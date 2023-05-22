#include "StageEventHandler_S1.h"
#include "Scene_Battle.h"
#include "ScreenManager.h"
#include "Enemy_Infary.h"
#include "GameManager.h"
#include "Game_TestBox.h"

void StageEventHandler_S1::Update(DWORD dt)
{
	Game_Screen* screen = ScreenManager::GetInstance()->Screen();

	// Make Camera focus to player
	//Set_Camera_Focus_Player();

	// Fix camera position
	Game_SweeperBlock* sweeper = GetSweeper();
	float px, py;
	_srcScene->p1()->GetCenterPoint(px, py);

	if (px > _maxMovedLength && _maxMovedLength < MAX_MOVEABLE_LENGTH_STAGE_1)
	{
		_maxMovedLength = px;
	}
	else if (_maxMovedLength > MAX_MOVEABLE_LENGTH_STAGE_1)
	{
		_maxMovedLength = MAX_MOVEABLE_LENGTH_STAGE_1;
	}

	if (!_toggleFreeCam)
	{
		screen->SetPosition(_maxMovedLength - screen->width()/2.0f, screen->height());
		if (screen->x() + screen->width() > _srcScene->MapWidth())
			screen->SetPosition(_srcScene->MapWidth() - screen->width(), screen->height());

		//else if (screen->x() < sweeper->x() + sweeper->width())
		//	screen->SetPosition(sweeper->x() + sweeper->width(), screen->height());
		//else
		//	screen->SetPosition(screen->x(), screen->height());
		//fix sweeper position
		//sweeper->SetPosition(screen->x() - GetSweeper()->width(), screen->height());
	}

	//sweeper->SetPosition(_maxMovedLength - screen->width()/2.0f - sweeper->width(), screen->height());
	sweeper->SetPosition(_maxMovedLength - screen->width() / 2.0f - sweeper->width()+10, screen->height());
	float l, t, b, r;
	sweeper->GetLTRB(l, t, r, b);
	_srcScene->spatial->update(_sweeperID,(int) l,(int) b,(int) r,(int) t);
}

void StageEventHandler_S1::Load()
{
	_srcScene->SetMapSize(3328, GAMESCREEN_HEIGHT);

	SoundSystem* SS = SoundSystem::getInstance();
	SS->playBGM(BGM_JUNGLE);

	// Parse map
	_srcScene->init_spatial();
	_srcScene->parseMap("textures\\MAP1");

	//_srcScene->_ParseSection_DICT("textures\\MAP1");
	//_srcScene->_ParseOBject("textures\\MAP1");

	// Add sweeper block
	unique_ptr<Game_SweeperBlock> sweeper(new Game_SweeperBlock(-32, GAMESCREEN_HEIGHT, Z_INDEX_TERRAIN, 32, GAMESCREEN_HEIGHT));
	_sweeperID =  _srcScene->add_object(move(sweeper));
	//_srcScene->spatial->insert_exception(_sweeperID);
}

void StageEventHandler_S1::CompleteStage()
{
	GameManager::GetInstance()->ReceiveSignal(SIG_LOADING_STAGE_3, _srcScene);
	_srcScene->PAUSE();
}

Game_SweeperBlock* StageEventHandler_S1::GetSweeper()
{
	return (Game_SweeperBlock*)(_srcScene->getObjectByID(_sweeperID));
}

// ===================================================================
// EVENTS


void StageEventHandler_S1::HelpGetRevivePoint(float& posX, float& posY)
{
	Game_SweeperBlock* sweeper = GetSweeper();
	unique_ptr<Game_TestBox>testbox(new Game_TestBox(0, 0, 0, PLAYER_BASE_WIDTH, PLAYER_BASE_HEIGHT, 0, 0));

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	vector<int> id_list = ScreenManager::GetInstance()->Screen()->Get_ObjectsID_InsideScreen(scene->spatial, GET_OBJECTS_RANGE);
	vector<PGAMEOBJECT>* coObjects = scene->getObjectById(id_list);

	Game_Screen* screen = ScreenManager::GetInstance()->Screen();

	float adding = -8;

	bool canSpawn = false;
	while (!canSpawn && testbox->x() + testbox->width() < _srcScene->MapWidth())
	{
		adding += 32;
		posX = sweeper->x() + sweeper->width() + adding;
		posY = _srcScene->MapHeight() - 16;
		testbox->SetPosition(posX, posY);

		// Make testbox move down
		testbox->SetSpeed(0, -scene->MapWidth());
		testbox->Update(1, coObjects);
		// Get Collisions and handle them.
		vector<PCOLLISIONEVENT>* coEvents = testbox->GetCollisionList();
		for (int i = 0; i < coEvents->size(); i++)
		{
			PCOLLISIONEVENT e = coEvents->at(i);
			// Check if under player have any terrain
			if (dynamic_cast<Game_DeadlyBlock*>(e->obj))
			{
				canSpawn = false;
				break;
			}

			if (dynamic_cast<Game_Terrain*>(e->obj))
			{
				canSpawn = true;
				break;
			}
		}
	}

	if (!canSpawn)
	{
		posX = sweeper->x() + sweeper->width() + 16;
		posY = _srcScene->MapHeight() - 16;
	}
}