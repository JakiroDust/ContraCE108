#pragma once
#include "StageEventHandler_Base.h"

class StageEventHandler_S3 : public StageEventHandler_Base
{
	private:
		DWORD spawn_infary_ticker = 0;
		void Spawn_Infary(DWORD dt, float camX, float spawnPosY);
	public:
		StageEventHandler_S3(Scene_Battle* src) : StageEventHandler_Base(src)
		{
			_srcScene = src;
		}

		void Update(DWORD dt) override;
		void Load() override;
};

