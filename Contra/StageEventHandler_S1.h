#pragma once
#include "StageEventHandler_Base.h"
#include "Game_SweeperBlock.h"

#define MAX_MOVEABLE_LENGTH_STAGE_1 3200
#define BOSS_TRIGGER_RANGE_STAGE_1 3072
#define SWEEPER_TRIGGERED_SPEED_S1 0.1f 

class StageEventHandler_S1 : public StageEventHandler_Base
{
	private:
		int _sweeperID;
		float _maxMovedLength;
		void Perform_StageClearEvent(DWORD dt) override;
	public:
		StageEventHandler_S1(Scene_Battle* src) : StageEventHandler_Base(src)
		{
			_srcScene = src;
		}
		Game_SweeperBlock* GetSweeper();
		void Update(DWORD dt) override;
		void SpecificUpdate(DWORD dt, Game_ObjectBase* obj) override;
		void Load() override;
		void CompleteStage() override;

		virtual void HelpGetRevivePoint(float& posX, float& posY) override;
};

