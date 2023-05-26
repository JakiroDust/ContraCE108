#include "Scene_Start.h"
#include "GameManager.h"


using namespace std;
void Scene_Start::KeyDownEventHandler(int KeyCode)
{
	if (KeyCode == DIK_A)
		if (startTimer == false)
		{
			startTimer = true;
			int id = 1;	
			AddBlinkingDarkEffect(90, 165, 70.0f, 12.0f, id);

		}
}

void Scene_Start::init()
{
	AddImage_Static(GAMESCREEN_WIDTH / 2, GAMESCREEN_HEIGHT / 2, 0, 989900, 1, RENDER_MODE_CENTER);
}

void Scene_Start::Update(DWORD dt)
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

void Scene_Start::Render()
{
	vector<Game_Picture*> RenderQueue;

	for (auto& pic : _images)
	{
		Game_Picture* obj = pic.second.get();

		if (obj == NULL)
			continue;

		if (RenderQueue.size() == 0)
		{
			RenderQueue.push_back(obj);
			continue;
		}
		int j = int(RenderQueue.size());
		while (j > 0 && obj->z() < RenderQueue[j - 1]->z())
		{
			j--;
		}
		std::vector<Game_Picture*>::iterator it = RenderQueue.begin();
		RenderQueue.insert(it + j, obj);
	}
	float BG_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	CGame::GetInstance()->GetDirect3DDevice()->ClearRenderTargetView(CGame::GetInstance()->GetRenderTargetView(), BG_color);
	float x, y;
	ScreenManager::GetInstance()->Screen()->GetCenterPoint(x, y);
	for (int i = 0; i < RenderQueue.size(); i++)
	{
		RenderQueue[i]->Render();
	}
}

void Scene_Start::Load()
{
	SoundSystem* SS = SoundSystem::getInstance();
	SS->stopBGM();
	SS->playBGM(BGM_TITLE);
	init();
}

void Scene_Start::Unload()
{
	_images.clear();
}

void Scene_Start::nextScene()
{
	GameManager::GetInstance()->ReceiveSignal(SIG_LOADING_STAGE_1, this);
}


