#pragma once

#include <Windows.h>
#include <unordered_map>

#include "Sprites.h"
#include "AnimationFrame.h"

using namespace std;

class CAnimation
{
	ULONGLONG lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y);
	// Render using screen position instead of world location
	void RenderOnScreen(float x, float y, BYTE RenderMode = RENDER_MODE_CENTER,float ratiox=1,float ratioy=1);
	void Render(float x, float y,float width,float height);
	CAnimation* Clone_Flip();
};

typedef CAnimation* LPANIMATION;