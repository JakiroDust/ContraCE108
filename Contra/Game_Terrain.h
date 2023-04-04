#pragma once
#include "Game_StaticObject.h"

class Game_Terrain : public Game_StaticObject
{
	public:
		int objectType() { return TYPE_TERRAIN; }
		virtual bool IsBlocking() { return 1; }
		void SetNeedRender(bool) { _needRender = false; }
		bool NeedRender() { return false; }
};

