#pragma once
#include "Scene_Base.h"
#include "Game_Picture.h"

#define SCENE_LOADING_STAGE_WAIT_INTERVAL 1500

class Scene_LoadingStage : public Scene_Base
{
	private:
		unordered_map<int, unique_ptr<Game_Picture>> _images;
		int _StageID;
		void Init_Stage1();
		void Init_Stage3();
		void Finish_Loading();
		DWORD _waitingTick = 0;
		bool _finishLoading = false;
	public:
		Scene_LoadingStage(int stageId) : Scene_Base() { _StageID = stageId; }
		~Scene_LoadingStage() { Unload(); }
		void Update(DWORD dt) override;
		void Render() override;
		void Load() override;
		void Unload() override;
		void AddImage(float x, float y, int index, int spriteID, BYTE RenderMode);

		void AddImage_Static(float x, float y, int index, int spriteID,float ratio, BYTE RenderMode);

};

