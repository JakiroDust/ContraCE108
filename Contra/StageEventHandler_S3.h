#pragma once
#include "StageEventHandler_Base.h"
#include "Game_SweeperBlock.h"

#define MAX_MOVEABLE_LENGTH_STAGE_3 2048
#define BOSS_TRIGGER_RANGE_STAGE_3 1952
#define SWEEPER_TRIGGERED_SPEED_S3 0.1f 
#define S3_WAIT_FOR_BOSS_DIE 3000

class StageEventHandler_S3 : public StageEventHandler_Base
{
	private:
		int _sweeperID = -1;
		float _maxMovedLength = 0;
		DWORD _WaitForBossDie = 0;
		bool S3_firstJump = false;
		bool S3_BossDie = false;
		void Perform_StageClearEvent(DWORD dt) override;
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

