#include "Scene_GameOver.h"
#include "GameManager.h"
#define ContinueButton DIK_A
enum GameButton
{
	CONTINUE,
	END,
};
	
void Scene_GameOver::KeyDownEventHandler(int KeyCode)
{
	if (startTimer == true)
		return;
	switch (KeyCode)
	{
		case ContinueButton:
		{		
			switch (location)
			{

			case CONTINUE:
				GameManager::GetInstance()->reset_player_parameter();
				startTimer = true;
				break;
			case END:
				startTimer = true;
				endGame = true;
				break;
			}
		}
		break;
		case DIK_W: location = CONTINUE; _images[selection_id].get()->MoveToPoint(65, 135, 0); break;
		case DIK_S: location = END;		_images[selection_id].get()->MoveToPoint(65, 150, 0);  break;
		case DIK_UP: location = CONTINUE; _images[selection_id].get()->MoveToPoint(65, 135, 0); break;
		case DIK_DOWN: location = END;		_images[selection_id].get()->MoveToPoint(65, 150, 0);  break;
	}

	
}

void Scene_GameOver::init()
{
	int height;
	int start_dis;
	start_dis = 10;
	height = 30;
	AddText(start_dis, height, L"1P", id, 2.0f, RENDER_MODE_CENTER);
	start_dis = 80;
	AddNumber(start_dis, height, GameManager::GetInstance()->GetScore_P1(), id, 2, RENDER_MODE_CENTER);
	AddBlinkingDarkEffect(160.0f, 30.0f, 160, 10, id);
	//start_dis = 10;
	//height = 45;
	//AddText(start_dis, height, L"REST ", id, 2, RENDER_MODE_CENTER);
	//AddNumber(start_dis, height, GameManager::GetInstance()->GetSavedLife_P1(), id, 2, RENDER_MODE_CENTER);
	start_dis = 80;
	height = 60;
	AddText(start_dis, height, L"HI 00000", id, 2, RENDER_MODE_CENTER);
	AddBlinkingDarkEffect(150.0f, 60.0f, 80, 10, id);
	start_dis = 80;
	height = 120;
	wstring stage_name = L"GAME OVER";
	AddText(start_dis, height, stage_name.c_str(), id, 2, RENDER_MODE_CENTER);


	start_dis = 65;
	height = 135;
	selection_id = id;
	AddImage_Static(start_dis, height, id++, 979900,1, RENDER_MODE_CENTER);

	start_dis = 80;
	height = 135;
	AddText(start_dis, height, L"CONTINUE", id, 2, RENDER_MODE_CENTER);
	
	start_dis = 80;
	height = 150;
	AddText(start_dis, height, L"END", id, 2, RENDER_MODE_CENTER);
}

void Scene_GameOver::Update(DWORD dt)
{
	if (startTimer)
	{
		if (_waitingTick > dt)
		{
			_waitingTick -= dt;
		}
		else
		{
			nextScene();
			return;
		}
	}
	for (auto& pic : _images)
	{
		Game_Picture* obj = pic.second.get();
		if (obj != NULL)
			obj->Update(dt);
	}
}

void Scene_GameOver::Load()
{
	SoundSystem* SS = SoundSystem::getInstance();
	SS->stopBGM();
	SS->playBGM(BGM_GAME_OVER);
	init();
}

void Scene_GameOver::Unload()
{
	_images.clear();
}

void Scene_GameOver::nextScene()
{
	GameManager* gm = GameManager::GetInstance();

	if (endGame)
	{
		_NextScene(SIG_PLAY_INTRO);
		return;
	}

	gm->UseCoin();
	int currentStage = gm->GetCurrentStage();

	switch (currentStage)
	{
	case SCENE_STAGE_1:
		_NextScene(SIG_LOADING_STAGE_1);
		break;
	case SCENE_STAGE_3:
		_NextScene(SIG_LOADING_STAGE_3);
		break;
	}

}


