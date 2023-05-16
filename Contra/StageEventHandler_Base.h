#pragma once
#include "debug.h"

class Scene_Battle;

class StageEventHandler_Base
{
	protected:
		Scene_Battle* _srcScene;
		void Set_Camera_Focus_Player();
	public:
		StageEventHandler_Base(Scene_Battle* src)
		{
			_srcScene = src;
		}

		virtual void Update(DWORD dt) {}
		virtual void Load() {}
};

