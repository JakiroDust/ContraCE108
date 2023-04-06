#pragma once

#include "Texture.h"
#include "Game.h"

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
	void getAll(int& id, int& left, int& top, int& right, int& bottom, LPTEXTURE& tex);
};

typedef CSprite* LPSPRITE;