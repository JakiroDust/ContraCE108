#pragma once
#include "StageEventHandler_Base.h"
#include "Game_SweeperBlock.h"

class StageEventHandler_S3 : public StageEventHandler_Base
{
	private:
		int _sweeperID = -1;
		DWORD spawn_infary_ticker = 0;
		void Spawn_Infary(DWORD dt, float camX, float spawnPosY);
	public:
		StageEventHandler_S3(Scene_Battle* src) : StageEventHandler_Base(src)
		{
			_srcScene = src;
		}
		Game_SweeperBlock* GetSweeper();

		void Update(DWORD dt) override;
		void Load() override;

		void CompleteStage() override;
		virtual void HelpGetRevivePoint(float& posX, float& posY) override;
};

