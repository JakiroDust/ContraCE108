#include "StageEventHandler_S3.h"
#include "Scene_Battle.h"
#include "ScreenManager.h"
#include "Enemy_Infary.h"
#include "Game_TestBox.h"
#include "GameManager.h"

void StageEventHandler_S3::Update(DWORD dt)
{
	StageEventHandler_Base::Update(dt);

	// STAGE CLEAR
	GameManager* gm = GameManager::GetInstance();
	if (gm->Test_IfPassStage() == CAN_PASS_STAGE)
	{
		return;
	}

	//-----------------------------------------------------

	Game_Screen* screen = ScreenManager::GetInstance()->Screen();

	// Fix camera position
	Game_SweeperBlock* sweeper = GetSweeper();
	float px, py;
	_srcScene->p1()->GetCenterPoint(px, py);

	if (py > _maxMovedLength && _maxMovedLength < MAX_MOVEABLE_LENGTH_STAGE_3)
	{
		_maxMovedLength = py;
	}
	else if (_maxMovedLength > BOSS_TRIGGER_RANGE_STAGE_3
		&& _maxMovedLength < MAX_MOVEABLE_LENGTH_STAGE_3)
	{
		_maxMovedLength += SWEEPER_TRIGGERED_SPEED_S3 * dt;
		_maxMovedLength = min(MAX_MOVEABLE_LENGTH_STAGE_3, _maxMovedLength);
	}
	else if (_maxMovedLength >= MAX_MOVEABLE_LENGTH_STAGE_3)
	{
		_maxMovedLength = MAX_MOVEABLE_LENGTH_STAGE_3;
		// start boss fight
		if (GameManager::GetInstance()->Get_StagePasscardRemain() > 1)
		{
			GameManager::GetInstance()->Set_StagePasscardAmount(1);
		}
	}

	if (!_toggleFreeCam)
	{
		screen->SetPosition(0, _maxMovedLength + screen->height() / 2.0f);
		if (screen->y() - screen->height() <= 0)
			screen->SetPosition(0, screen->height());
		else if (screen->y() > _srcScene->MapHeight())
			screen->SetPosition(0, _srcScene->MapHeight());
	}

	// Update sweeper
	sweeper->SetPosition(0, _maxMovedLength - screen->height() / 2.0f + 2);
	float l, t, b, r;
	sweeper->GetBoundingBox(l, t, r, b);
	_srcScene->spatial->update(_sweeperID, (int)l, (int)b, (int)r, (int)t);
}

void StageEventHandler_S3::Load()
{
	_srcScene->SetMapSize(GAMESCREEN_WIDTH, 2176);

	SoundSystem* SS = SoundSystem::getInstance();
	SS->playBGM(BGM_JUNGLE);

	// Parse map
	_srcScene->init_spatial();
	_srcScene->parseMap("textures\\MAP3");

	// Add sweeper block
	unique_ptr<Game_SweeperBlock> sweeper(new Game_SweeperBlock(0, 0, Z_INDEX_TERRAIN, GAMESCREEN_WIDTH, 32, true));
	_sweeperID = _srcScene->add_object(move(sweeper));

	// setOther game params
	GameManager::GetInstance()->Set_StagePasscardAmount(2);

	// default load
	StageEventHandler_Base::Load();
}

void StageEventHandler_S3::CompleteStage()
{
	StageEventHandler_Base::CompleteStage();
	GameManager::GetInstance()->ReceiveSignal(SIG_PLAY_INTRO, _srcScene);
	_srcScene->PAUSE();
}

Game_SweeperBlock* StageEventHandler_S3::GetSweeper()
{
	return (Game_SweeperBlock*)(_srcScene->getObjectByID(_sweeperID));
}

// ===================================================================
// EVENTS

void StageEventHandler_S3::HelpGetRevivePoint(float& posX, float& posY)
{
	Game_SweeperBlock* sweeper = GetSweeper();
	unique_ptr<Game_TestBox>testbox(new Game_TestBox(0, 0, 0, PLAYER_BASE_WIDTH, PLAYER_BASE_HEIGHT, 0, 0));

	Scene_Battle* scene = (Scene_Battle*)(ScreenManager::GetInstance()->Scene());

	vector<int> id_list = ScreenManager::GetInstance()->Screen()->Get_ObjectsID_InsideScreen(scene->spatial.get(), GET_OBJECTS_RANGE);
	vector<PGAMEOBJECT>* coObjects = scene->getObjectByIDList(id_list);

	Game_Screen* screen = ScreenManager::GetInstance()->Screen();
	float cx, cy;
	screen->GetPosition(cx, cy);

	float adding = -8;

	bool canSpawn = false;
	while (!canSpawn && testbox->x() + testbox->width() < _srcScene->MapWidth())
	{
		adding += 32;
		posX = adding;
		posY = _maxMovedLength;
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

			if (dynamic_cast<Game_Terrain*>(e->obj)
				|| dynamic_cast<Game_Blocker*>(e->obj))
			{
				canSpawn = true;
				break;
			}
		}
	}

	if (!canSpawn)
	{
		posX = screen->width()/2;
		posY = _maxMovedLength;
	}
}

void StageEventHandler_S3::Perform_StageClearEvent(DWORD dt)
{
	Game_Player* player = _srcScene->p1();
	player->SetAuto(true);
	//player->SetImmortal(true);
	// SCENE: boss die
	if (!S3_BossDie)
	{
		S3_BossDie = true;
		_WaitForBossDie = S3_WAIT_FOR_BOSS_DIE;
	}

	if (_WaitForBossDie > dt)
	{
		_WaitForBossDie -= dt;
		return;
	}

	// SCENE: player move to base 
	if (abs(player->x() - _srcScene->MapWidth()/2.0f) > 32)
	{
		if (!player->Test_IfHaveAction())
		{
			if (player->x() <= _srcScene->MapWidth() / 2.0f)
				player->AddAction(DIK_RIGHT);
			else
				player->AddAction(DIK_LEFT);
		}
	}
	else if (player->y() < 2036)
	{
		if (!player->Test_IfHaveAction())
		{
			player->AddAction(-1);
			if (!S3_firstJump && !player->IsOnGround())
			{
				// do nothing, wait to player stand on ground
			}
			else if (!S3_firstJump && player->IsOnGround())
			{
				player->AddAction(DIK_P);
				S3_firstJump = true;
			}
		}
	}
	else
	{
		player->teleport(_srcScene->MapWidth() + 100, _srcScene->MapHeight());
		if (_WaitForClearStage >= WAIT_STAGECLEAR_MAXVALUE)
		{
			_WaitForClearStage = 1000;
		}
	}
}