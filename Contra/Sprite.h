#pragma once

#include "Texture.h"
#include "Game.h"
#include "STL_storage.h"
class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex, bool isMirror = false);

	
	void Draw(float x, float y);
	void Draw(float x, float y, const int width,const int heigth);
	void Draw(float x, float y, int& width, int& heigth);
	void Draw(float x, float y,float&width,float&heigth);
	void getAll(int& id, int& left, int& top, int& right, int& bottom, LPTEXTURE& tex);
	void getWH(float& width, float& heigth) { width = abs(right - left)/1.0f; heigth = abs(top - bottom)/1.0f; }
};

typedef CSprite* LPSPRITE;