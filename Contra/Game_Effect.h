#pragma once
#include "Game_StaticObject.h"
class Game_Effect : public Game_StaticObject
{
	protected:

		// wait before start render
		DWORD _DelayTick = 0;
		int _startSFX = 0;
	public:
		Game_Effect(float x, float y, int z, int aniID, DWORD offset = 0,int ENDSFX=-1) : Game_StaticObject(x, y, z, 1, 1)
		{
			_SpriteId = aniID;
			_DelayTick = offset;
			_startSFX = ENDSFX;
		}
		int objectType() { return TYPE_LAYER; }

		~Game_Effect()
		{
			Cleaning();
		}

		void Update(DWORD dt) override;
		void Render() override;;
};

