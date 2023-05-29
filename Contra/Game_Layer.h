#pragma once
#include "Game_StaticObject.h"
class Game_Layer : public Game_StaticObject
{
protected:

public:
	Game_Layer(float x, float y, int z, int width, int height) : Game_StaticObject(x, y, z, width, height) {};
	int objectType() { return TYPE_LAYER; }
	void Render() override
	{
		RenderHitbox();
		if (_SpriteId > 0)
		{
			CAnimations* animations = CAnimations::GetInstance();
			float x, y;
			GetCenterPoint(x, y);
			animations->Get(_SpriteId)->Render(x, y);
		}

	}
};

