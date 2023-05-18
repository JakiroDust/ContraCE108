#pragma once
#include "debug.h"
#include "StageEventHandler_S1.h"
#include "StageEventHandler_S3.h"
#include "Scene_LoadingStage.h"
#include "ScreenManager.h"
#include "Textures.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	10

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2
#define ASSETS_SECTION_DICT 3

#define MAX_SCENE_LINE 1024

#define SIG_PLAY_INTRO 1200
#define SIG_PlAY_END_GAME 1201
#define SIG_PLAY_ASK_REVIVE 1202
#define SIG_PLAY_STAGE_1 1001
#define SIG_PLAY_STAGE_2 1002
#define SIG_PLAY_STAGE_3 1003
#define SIG_PLAY_STAGE_4 1004
#define SIG_LOADING_STAGE_1 1101
#define SIG_LOADING_STAGE_2 1102
#define SIG_LOADING_STAGE_3 1103
#define SIG_LOADING_STAGE_4 1104

#define SCENE_BLANK_SCREEN 0
#define SCENE_STAGE_1 10001
#define SCENE_STAGE_2 10002
#define SCENE_STAGE_3 10003
#define SCENE_STAGE_4 10004

typedef unsigned int UINT;

class GameManager
{
	private:
		static GameManager* __instance;

		// signal
		
		int _signal = -1;
		Scene_Base* _signalSender = NULL;
		void SignalHandler();

		// stage

		UINT _coin = 0;
		UINT _P1_score = 0;
		UINT _P2_score = 0;
		int _stagePasscard = 0;

		void InitGame();

		// scene
		void Create_Stage_1(Scene_Battle* scene);
		void Create_Stage_3(Scene_Battle* scene);
		void Create_LoadingStage(Scene_LoadingStage* scene, int stageID);
		void _ParseSection_SPRITES(string line);
		void _ParseSection_ANIMATIONS(string line);

		

		void _ParseSection_TEXTURES(string line);

		void _ParseSection_ASSETS(string line);
		void LoadAssets(LPCWSTR assetFile);
	public:
		void Load(LPCWSTR gameFile);
		static GameManager* GetInstance();
		GameManager() {}

		void Update(DWORD dt);

		// Scene control

		void ReceiveSignal(int signal, Scene_Base* sender);
		void StartApplication();

		// Game control
		
		void GainScore_P1(UINT score) { _P1_score += score; }
		void GainScore_P2(UINT score) { _P2_score += score; }
		void UseCoin() { _coin > 0 ? _coin-- : 0 ; }

		UINT GetScore_P1() { return _P1_score; }
		UINT GetScore_P2() { return _P2_score; }
		UINT GetCoin() { return _coin; }

		void Gain_StagePasscard(int amount = 1) { _stagePasscard -= amount; }
		StageEventHandler_Base* Get_StageEventHandler(int stage, Scene_Battle* scene);

};

