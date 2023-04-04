#include "Game_ObjectBase.h"
using namespace std;

Game_ObjectBase::Game_ObjectBase(float x, float y, int z, int width, int height)
{
	_x = x;
	_y = y;
	_z = z;
	_width = width;
	_height = height;
}

void Game_ObjectBase::Render()
{
	if (!_needRender) return;
	CAnimations* animations = CAnimations::GetInstance();
	float x, y;
	GetCenterPoint(x, y);
	animations->Get(_SpriteId)->Render(x, y);
}

void Game_ObjectBase::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _x;
	top = _y;
	right = _x + _width;
	bottom = _y + _height;
}