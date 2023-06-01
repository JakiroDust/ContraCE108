#pragma once
#include "Game_StaticObject.h"
class Game_Effect : public Game_StaticObject
{
protected:

public:
	Game_Effect(float x, float y, int z, int aniID) : Game_StaticObject(x, y, z, 1, 1)
	{
		_SpriteId = aniID;
	}
	int objectType() { return TYPE_LAYER; }

	void Update(DWORD dt) override;
	void Render() override;
};

