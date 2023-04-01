#pragma once
#include "Game_ObjectBase.h"
class Game_Object : public Game_ObjectBase
{
	protected:
	public:
		virtual int objectType() = 0;
		// 0 - Terrain
		// 1 - Event
		// 2 - Animation
		bool isEntity();
		bool isObject();
};

