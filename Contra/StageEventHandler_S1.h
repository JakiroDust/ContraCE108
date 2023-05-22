#pragma once
#include "StageEventHandler_Base.h"
#include "Game_SweeperBlock.h"

#define SPAWN_INFARY_INTERVAL 1500
#define SPAWN_INFARY_RANDOM_MAX 20
#define MAX_MOVEABLE_LENGTH_STAGE_1 3072 

class StageEventHandler_S1 : public StageEventHandler_Base
{
	private:
		int _sweeperID;
		float _maxMovedLength;
		//void Spawn_Infary(DWORD dt, float camX, float spawnPosY);
	public:
		StageEventHandler_S1(Scene_Battle* src) : StageEventHandler_Base(src)
		{
			_srcScene = src;
		}
		Game_SweeperBlock* GetSweeper();
		void Update(DWORD dt) override;
		void Load() override;
		void CompleteStage() override;

		virtual void HelpGetRevivePoint(float& posX, float& posY) override;
};

