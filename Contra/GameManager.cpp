#include "GameManager.h"
#include "ScreenManager.h"

GameManager* GameManager::__instance = NULL;

GameManager* GameManager::GetInstance()
{
	if (__instance == NULL) __instance = new GameManager();
	return __instance;
}


void GameManager::Update(DWORD dt)
{
	SignalHandler();
}

void GameManager::SignalHandler()
{
	switch (_signal)
	{
	case SIG_PLAY_STAGE_1:
		Create_Stage_1(NULL);
		break;
	case SIG_PLAY_STAGE_3:
		Create_Stage_1(NULL);
		break;
	case SIG_LOADING_STAGE_1:
		Create_LoadingStage(NULL, SCENE_STAGE_1);
		break;
	case SIG_LOADING_STAGE_3:
		Create_LoadingStage(NULL, SCENE_STAGE_3);
		break;
	default:
		break;
	}
	_signal = 0;
	_signalSender = NULL;
}

void GameManager::ReceiveSignal(int signal, Scene_Base* sender)
{
	_signal = signal;
	_signalSender = sender;
}

StageEventHandler_Base* GameManager::Get_StageEventHandler(int stage, Scene_Battle* scene)
{
	StageEventHandler_Base* handler;
	switch (stage)
	{
	case SCENE_STAGE_1:
		handler = new StageEventHandler_S1(scene);
		return handler;
		break;
	default:
		DebugOut(L"[ERROR] Unknown Stage id. Get StageEventHandler failed.\n");
		return NULL;
	}
}

void GameManager::InitGame()
{
	_coin = 3;
	_P1_score = 0;
	_P2_score = 0;
}

void GameManager::StartApplication()
{
	ScreenManager* screenManager = ScreenManager::GetInstance();

	// currently Intro 've not implemented yet . So start STAGE 1 instead.
	Create_LoadingStage(NULL, SCENE_STAGE_1);
}

//======================================================================================
// CREATE SCENE

void GameManager::Create_Stage_1(Scene_Battle* scene)
{
	if (scene == NULL)
	{
		ScreenManager* screenManager = ScreenManager::GetInstance();
		screenManager->Create_Scene_Battle();
		scene = (Scene_Battle*)(screenManager->Scene());
	}

	scene->SetStageEventHandler(Get_StageEventHandler(SCENE_STAGE_1, scene));

	// create stage 1 mean just at the beginning of the game
	// init game
	InitGame();

	scene->Load();
}

void GameManager::Create_LoadingStage(Scene_LoadingStage* scene, int stageID)
{
	if (scene == NULL)
	{
		ScreenManager* screenManager = ScreenManager::GetInstance();
		screenManager->Create_Scene_LoadingStage(stageID);
		scene = (Scene_LoadingStage*)(screenManager->Scene());
	}

	scene->Load();
}