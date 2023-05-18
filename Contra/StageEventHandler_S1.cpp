#include "StageEventHandler_S1.h"
#include "Scene_Battle.h"
#include "ScreenManager.h"
#include "Enemy_Infary.h"
#include "GameManager.h"
#include "Game_TestBox.h"

void StageEventHandler_S1::Update(DWORD dt)
{

	// Make Camera focus to player
	Set_Camera_Focus_Player();

	// Execute event base on camera position
	Game_Screen* screen = ScreenManager::GetInstance()->Screen();
	float cx, cy;
	screen->GetPosition(cx, cy);


	if (cx >= 160 && cx <= 512)
	{
		Spawn_Infary(dt, cx, 160);
		if (cx <= 192)
		{
			Spawn_Infary(dt, cx, 130);
		}
	}	
	else if (cx >= 960 && cx <= 1120)
	{
		Spawn_Infary(dt, cx, 160);
	}
	else if (cx >= 1184 && cx <= 1600)
	{
		Spawn_Infary(dt, cx, 190);
		if (cx >= 1376 && cx <= 1504)
		{
			Spawn_Infary(dt, cx, 160);
		}
	}
	else if (cx >= 1696 && cx <= 1760)
	{
		Spawn_Infary(dt, cx, 160);
	}
	else if (cx >= 1824 && cx <= 1920)
	{
		Spawn_Infary(dt, cx, 190);
	}
	else if (cx >= 2080 && cx <= 2112)
	{
		Spawn_Infary(dt, cx, 160);
	}
	else if (cx >= 2112 && cx <= 2144)
	{
		Spawn_Infary(dt, cx, 130);
	}
	else if (cx >= 2208 && cx <= 2272)
	{
		Spawn_Infary(dt, cx, 190);
	}
	else if (cx >= 2400 && cx <= 2496)
	{
		Spawn_Infary(dt, cx, 130);
	}
	else if (cx >= 2784 && cx <= 2848)
	{
		Spawn_Infary(dt, cx, 160);
	}

	// fix sweeper position
	GetSweeper()->SetPosition(cx - GetSweeper()->width(), cy);
}

void StageEventHandler_S1::Load()
{
	_srcScene->SetMapSize(3328, GAMESCREEN_HEIGHT);
	ScreenManager::GetInstance()->Screen()->SetViewBox(_srcScene->MapWidth(), _srcScene->MapHeight());

	SoundSystem* SS = SoundSystem::getInstance();
	SS->playBGM(BGM_JUNGLE);

	// Parse map
	_srcScene->init_spatial();
	_srcScene->parseMap("textures\\MAP1");

	//_srcScene->_ParseSection_DICT("textures\\MAP1");
	//_srcScene->_ParseOBject("textures\\MAP1");

	// Add sweeper block
	unique_ptr<Game_SweeperBlock> sweeper(new Game_SweeperBlock(-64, 0, Z_INDEX_TERRAIN, 64, GAMESCREEN_HEIGHT));
	_sweeperID =  _srcScene->add_object(move(sweeper));
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

void StageEventHandler_S1::Spawn_Infary(DWORD dt, float camX, float spawnPosY)
{
	if (random_seed < SPAWN_INFARY_RANDOM_MAX)
		random_seed++;
	else
		random_seed = 0;
	
	if (spawn_infary_ticker >= dt + random_seed)
	{
		spawn_infary_ticker -= dt + random_seed;
		return;
	}
	spawn_infary_ticker = SPAWN_INFARY_INTERVAL;

	for (int i = 0; i < 1; i++)
	{
		unique_ptr <Enemy_Infary> redgunner(new Enemy_Infary(camX + GAMESCREEN_WIDTH + 28, spawnPosY, Z_INDEX_ENEMY));
		_srcScene->add_object(move(redgunner));
	}
}

void StageEventHandler_S1::HelpGetRevivePoint(float& posX, float& posY)
{
	Game_SweeperBlock* sweeper = GetSweeper();
	unique_ptr<Game_TestBox>testbox(new Game_TestBox(0, 0, 0, PLAYER_BASE_WIDTH, PLAYER_BASE_HEIGHT, 0, 0));

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	vector<int> id_list = scene->getNearbyIDFast();
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