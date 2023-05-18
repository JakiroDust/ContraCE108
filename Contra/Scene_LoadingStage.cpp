#include "Scene_LoadingStage.h"
#include "GameManager.h"
#include "Contra_ANI_ID.h"

void Scene_LoadingStage::Update(DWORD dt)
{
	if (_finishLoading)
		return;

	if (_waitingTick > dt)
	{
		_waitingTick -= dt;
	}
	else
	{
		Finish_Loading();
		return;
	}

	for (auto& pic : _images)
	{
		Game_Picture* obj = pic.second.get();
		if (obj != NULL)
			obj->Update(dt);
	}
}

void Scene_LoadingStage::Render()
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

	for (int i = 0; i < RenderQueue.size(); i++)
	{
		RenderQueue[i]->Render();
	}
}

void Scene_LoadingStage::Load()
{
	SoundSystem* SS = SoundSystem::getInstance();
	SS->stopBGM();

	switch (_StageID)
	{
	case SCENE_STAGE_1:
		Init_Stage1();
		break;
	case SCENE_STAGE_3:
		Init_Stage3();
		break;
	}

	_waitingTick = SCENE_LOADING_STAGE_WAIT_INTERVAL;
}

void Scene_LoadingStage::Unload()
{
	_images.clear();
}

void Scene_LoadingStage::AddImage(float x, float y, int index, int spriteID, BYTE RenderMode)
{	
	if (_images[index] != NULL)
	{
		_images[index].reset(new Game_Picture(x, y, index, spriteID, RenderMode));
	}
	else
	{
		unique_ptr <Game_Picture> image(new Game_Picture(x, y, index, spriteID, RenderMode));
		_images[index] = move(image);
	}
}

void Scene_LoadingStage::Init_Stage1()
{
	AddImage(GAMESCREEN_WIDTH/2, GAMESCREEN_HEIGHT/2, 1, CONTRA_ANI_WALK_RIGHT, RENDER_MODE_CENTER);
}

void Scene_LoadingStage::Init_Stage3()
{
	AddImage(GAMESCREEN_WIDTH / 2, GAMESCREEN_HEIGHT / 2, 1, CONTRA_ANI_WALK_LEFT, RENDER_MODE_CENTER);
}

void Scene_LoadingStage::Finish_Loading()
{
	switch (_StageID)
	{
	case SCENE_STAGE_1:
		GameManager::GetInstance()->ReceiveSignal(SIG_PLAY_STAGE_1, this);
		break;
	case SCENE_STAGE_3:
		GameManager::GetInstance()->ReceiveSignal(SIG_PLAY_STAGE_3, this);
		break;
	}
	_finishLoading = true;
}