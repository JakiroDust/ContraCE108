#include "Scene_LoadingStage.h"
#include "GameManager.h"
#include "Contra_ANI_ID.h"
#include "Word.h"
#include "Game_Picture_Static.h"
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
	float BG_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	CGame::GetInstance()->GetDirect3DDevice()->ClearRenderTargetView(CGame::GetInstance()->GetRenderTargetView(), BG_color);
	float x, y;
	ScreenManager::GetInstance()->Screen()->GetCenterPoint(x, y);
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
void Scene_LoadingStage::AddImage_Static(float x, float y, int index, int spriteID,float ratio, BYTE RenderMode)
{
	if (_images[index] != NULL)
	{
		_images[index].reset(new Game_Picture_Static(x, y, index, spriteID,ratio, RenderMode));
	}
	else
	{
		unique_ptr <Game_Picture_Static> image(new Game_Picture_Static(x, y, index, spriteID,ratio, RenderMode));
		_images[index] = move(image);
	}
}
void Scene_LoadingStage::Init_Stage1()
{
	int id = 1;
	int id2 = GAMESCREEN_WIDTH / 5;
	AddImage(GAMESCREEN_WIDTH/2, GAMESCREEN_HEIGHT/2, id++, CONTRA_ANI_WALK_RIGHT, RENDER_MODE_CENTER);
	int height = GAMESCREEN_HEIGHT - 10;
	AddImage_Static(id2 = id2 + 9, height, id++, WORDSPRITE::getCharacterSpriteID(L'L'), 2, RENDER_MODE_CENTER);
	AddImage_Static(id2 = id2 + 9, height, id++, WORDSPRITE::getCharacterSpriteID(L'O'), 2, RENDER_MODE_CENTER);
	AddImage_Static(id2 = id2 + 9, height, id++, WORDSPRITE::getCharacterSpriteID(L'A'), 2, RENDER_MODE_CENTER);
	AddImage_Static(id2 = id2 + 9, height, id++, WORDSPRITE::getCharacterSpriteID(L'D'), 2, RENDER_MODE_CENTER);
	id2 = id2 + 9;
	AddImage_Static(id2=id2+9,height, id++, WORDSPRITE::getNumberSpriteID(1),2, RENDER_MODE_CENTER);
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