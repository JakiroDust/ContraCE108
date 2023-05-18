#include "GameManager.h"
#include "ScreenManager.h"

#define GAME_FILE_SECTION_UNKNOWN 0
#define MAX_GAME_LINE 100
#define GAME_FILE_SECTION_SETTINGS 1
#define GAME_FILE_SECTION_TEXTURES 2
#define GAME_FILE_SECTION_ASSESTS 3
GameManager* GameManager::__instance = NULL;
void GameManager::Load(LPCWSTR gameFile)
{
	DebugOut(L"[INFO] Start loading game file : %s\n", gameFile);

	ifstream f;
	f.open(gameFile);
	char str[MAX_GAME_LINE];

	// current resource section flag
	int section = GAME_FILE_SECTION_UNKNOWN;

	while (f.getline(str, MAX_GAME_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") { section = GAME_FILE_SECTION_SETTINGS; continue; }
		if (line == "[TEXTURES]") { section = GAME_FILE_SECTION_TEXTURES; continue; }
		if (line == "[ASSETS]") { section = GAME_FILE_SECTION_ASSESTS; continue; }
		if (line[0] == '[')
		{
			section = GAME_FILE_SECTION_UNKNOWN;
			DebugOut(L"[ERROR] Unknown section: %s\n", ToLPCWSTR(line));
			continue;
		}

		//
		// data section
		//
		switch (section)
		{
		//case GAME_FILE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case GAME_FILE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case GAME_FILE_SECTION_ASSESTS: _ParseSection_ASSETS(line); break;
		
		}
	}
	f.close();

	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", gameFile);
}


void GameManager::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);

	CTextures::GetInstance()->Add(texID, path.c_str());
}

void GameManager::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}
void GameManager::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}
void GameManager::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}



void GameManager::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

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
		Create_Stage_3(NULL);
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
	case SCENE_STAGE_3:
		handler = new StageEventHandler_S3(scene);
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

void GameManager::Create_Stage_3(Scene_Battle* scene)
{
	if (scene == NULL)
	{
		ScreenManager* screenManager = ScreenManager::GetInstance();
		screenManager->Create_Scene_Battle();
		scene = (Scene_Battle*)(screenManager->Scene());
	}

	scene->SetStageEventHandler(Get_StageEventHandler(SCENE_STAGE_3, scene));

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