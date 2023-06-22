#include "Scene_Credit.h"
#include "GameManager.h"
void Scene_Credit::init()
{
	int height;
	int start_dis;
	int const word_Dis = 15;
	int const START_DIS = 5;
	start_dis = START_DIS;
	height = 30;
	AddText(start_dis, height, L"CONGRATULATIONS", id, 2.0f, RENDER_MODE_CENTER);
	start_dis = START_DIS;
	height = 30+ word_Dis;
	AddText(start_dis, height, L"YOU VE DESTROYED THE VILE", id, 2.0f, RENDER_MODE_CENTER);
	start_dis = START_DIS;
	height = 30 + word_Dis*2;
	AddText(start_dis, height, L"RED FALCON AND SAVED THE", id, 2.0f, RENDER_MODE_CENTER);
	start_dis = START_DIS;
	height = 30 + word_Dis * 3;
	AddText(start_dis, height, L"UNIVERSE", id, 2.0f, RENDER_MODE_CENTER);
	start_dis = START_DIS;
	height = 30 + word_Dis * 4;
	AddText(start_dis, height, L"CONSIDER YOURSELF A HERO", id, 2.0f, RENDER_MODE_CENTER);
	start_dis = START_DIS;
	height = 30 + word_Dis * 16;
	AddText(start_dis, height, L"          STAFF", id, 2.0f, RENDER_MODE_CENTER);
	start_dis = START_DIS;
	height = 30 + word_Dis * 17;
	AddText(start_dis, height, L"     HUYNH DANG QUANG", id, 2.0f, RENDER_MODE_CENTER);
	start_dis = START_DIS;
	height = 30 + word_Dis * 18;
	AddText(start_dis, height, L"       TRAN DUC HUY", id, 2.0f, RENDER_MODE_CENTER);
	start_dis = START_DIS;
	height = 30 + word_Dis * 19;
	AddText(start_dis, height, L"      NGUYEN ANH PHI", id, 2.0f, RENDER_MODE_CENTER);
	for (auto& i : _images)

	{
		i.second.get()->MoveToPointADD(0, -(30 + word_Dis * 9), _waitingTick-4000);
	}
}


void Scene_Credit::KeyDownEventHandler(int KeyCode)
{
	if (KeyCode == DIK_A)
		if (startTimer == false)
		{
			startTimer = true;
			_waitingTick = 0;

		}
}

void Scene_Credit::Update(DWORD dt)
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
void Scene_Credit::Load()
{
	SoundSystem* SS = SoundSystem::getInstance();
	SS->stopBGM();
	SS->playBGM(BGM_ENDING);
	init();
}

void Scene_Credit::Unload()
{
	_images.clear();
}

void Scene_Credit::nextScene()
{
	_NextScene(SIG_PLAY_INTRO);

}

