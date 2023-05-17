#pragma once
#include "StageEventHandler_Base.h"
#include "Game_SweeperBlock.h"

#define SPAWN_INFARY_INTERVAL 1200

class StageEventHandler_S1 : public StageEventHandler_Base
{
	private:
		unique_ptr<Game_SweeperBlock> _sweeper;
		DWORD spawn_infary_ticker = 0;
		void Spawn_Infary(DWORD dt, float camX, float spawnPosY);
	public:
		StageEventHandler_S1(Scene_Battle* src) : StageEventHandler_Base(src)
		{
			_srcScene = src;
		}

		void Update(DWORD dt) override;
		void Load() override;
		void CompleteStage() override;
};

