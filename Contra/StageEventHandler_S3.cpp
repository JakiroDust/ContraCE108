#include "StageEventHandler_S3.h"
#include "Scene_Battle.h"
#include "ScreenManager.h"
#include "Enemy_Infary.h"
#include "Game_TestBox.h"
#include "GameManager.h"

void StageEventHandler_S3::Update(DWORD dt)
{
	// Make Camera focus to player
	Set_Camera_Focus_Player();

	// Execute event base on camera position
	Game_Screen* screen = ScreenManager::GetInstance()->Screen();
	float cx, cy;
	screen->GetPosition(cx, cy);

	//if (cx >= 224 && cx <= 544)
	//{
	//	Spawn_Infary(dt, cx, 160);
	//}

		// fix sweeper position
	GetSweeper()->SetPosition(0, cy - GAMESCREEN_HEIGHT);
}

void StageEventHandler_S3::Load()
{
	_srcScene->SetMapSize(GAMESCREEN_WIDTH, 2176);
	ScreenManager::GetInstance()->Screen()->SetViewBox(_srcScene->MapWidth(), _srcScene->MapHeight());

	SoundSystem* SS = SoundSystem::getInstance();
	SS->playBGM(BGM_JUNGLE);

	// Parse map
	_srcScene->init_spatial();
	_srcScene->parseMap("textures\\MAP3");

	//_srcScene->_ParseSection_DICT("textures\\MAP1");
	//_srcScene->_ParseOBject("textures\\MAP1");

	// Add sweeper block
	unique_ptr<Game_SweeperBlock> sweeper(new Game_SweeperBlock(0, 0, Z_INDEX_TERRAIN, GAMESCREEN_WIDTH, 32));
	_sweeperID = _srcScene->add_object(move(sweeper));
}

void StageEventHandler_S3::CompleteStage()
{
	GameManager::GetInstance()->ReceiveSignal(SIG_LOADING_STAGE_1, _srcScene);
	_srcScene->PAUSE();
}

Game_SweeperBlock* StageEventHandler_S3::GetSweeper()
{
	return (Game_SweeperBlock*)(_srcScene->getObjectByID(_sweeperID));
}

// ===================================================================
// EVENTS

void StageEventHandler_S3::Spawn_Infary(DWORD dt, float camX, float spawnPosY)
{
	//if (spawn_infary_ticker >= dt)
	//{
	//	spawn_infary_ticker -= dt;
	//	return;
	//}
	//spawn_infary_ticker = SPAWN_INFARY_INTERVAL;

	//for (int i = 0; i < 1; i++)
	//{
	//	unique_ptr <Enemy_Infary> redgunner(new Enemy_Infary(camX + GAMESCREEN_WIDTH / 2 + 32, spawnPosY, 2));
	//	_srcScene->add_object(move(redgunner));
	//}
}

void StageEventHandler_S3::HelpGetRevivePoint(float& posX, float& posY)
{
	Game_SweeperBlock* sweeper = GetSweeper();
	unique_ptr<Game_TestBox>testbox(new Game_TestBox(0, 0, 0, PLAYER_BASE_WIDTH, PLAYER_BASE_HEIGHT, 0, 0));

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	vector<int> id_list = scene->getNearbyIDFast();
	vector<PGAMEOBJECT>* coObjects = scene->getObjectById(id_list);

	Game_Screen* screen = ScreenManager::GetInstance()->Screen();
	float cx, cy;
	screen->GetCenterPoint(cx, cy);

	float adding = -8;

	bool canSpawn = false;
	while (!canSpawn && testbox->x() + testbox->width() < _srcScene->MapWidth())
	{
		adding += 32;
		posX = sweeper->x() + sweeper->width() + adding;
		posY = sweeper->height() + GAMESCREEN_HEIGHT / 2;
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
			if (dynamic_cast<Game_SweeperBlock*>(e->obj))
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
		posY = sweeper->height() + GAMESCREEN_HEIGHT/2;
	}
}