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
		return handler = new StageEventHandler_S1(scene);
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
	screenManager->Create_Scene_Battle();
	((Scene_Battle*)(screenManager->Scene()))->Create_Stage_Demo();
}
