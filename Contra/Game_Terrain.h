#pragma once
#include "Game_StaticObject.h"

class Game_Terrain : public Game_StaticObject
{
	public:
		Game_Terrain(float x, float y, int z, int width, int height) : Game_StaticObject(x, y, z, width, height) { }

		int objectType() { return TYPE_TERRAIN; }
		virtual bool IsBlocking() { return 1; }
		
		void Render() { RenderHitbox(); }
		void SetNeedRender(bool b) { _needRender = b; }
		bool NeedRender() { return _needRender; }
};

