#include "Game_Picture_Static.h"

Game_Picture_Static::Game_Picture_Static(float screenX, float screenY, int z, int spriteID,float ratio, BYTE RenderMode) :Game_Picture(_screenX, _screenY, z, _SpriteID, RenderMode)
{
	_screenX = screenX;
	_screenY = screenY;
	_ratio = ratio;
	_z = z;
	_SpriteID = spriteID;
	_RenderMode = RenderMode;
}

void Game_Picture_Static::Render()
{
	auto a = CSprites::GetInstance()->Get(_SpriteID);
	CSprites::GetInstance()->Get(_SpriteID)->DrawOnScreen(_screenX, _screenY, _RenderMode,_ratio);
}
