#pragma once

#include "Animation.h"
#include "Sprite.h"

class CAnimations
{
	static CAnimations* __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani, int isOneDirect = 0);
	LPANIMATION Get(int id);
	void Clear();

	static CAnimations* GetInstance();
};