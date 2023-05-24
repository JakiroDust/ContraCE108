#pragma once
#include "debug.h"

class Scene_Battle;
class Game_ObjectBase;

#define STAGE_DEBUG_ALLOW true

class StageEventHandler_Base
{
	protected:
		Scene_Battle* _srcScene;
		bool _toggleFreeCam = false;
		void Set_Camera_Focus_Player();

		void Debug_KeyDownEventHandler(int KeyCode);
	public:
		StageEventHandler_Base(Scene_Battle* src)
		{
			_srcScene = src;
		}

		virtual void Update(DWORD dt) {}
		virtual void SpecificUpdate(DWORD dt, Game_ObjectBase* obj) {}
		virtual void RenderHUD() {}
		virtual void Load() {}
		virtual void CompleteStage() {}
		virtual void KeyDownEventHandler(int KeyCode);

		virtual void HelpGetRevivePoint(float &posX, float &posY) { }
};

