#pragma once
#include "Game_Picture.h"
namespace WORDSPRITE
{

	int getNumberSpriteID(int number);
	Game_Picture createNumber(int number, float screenX, float screenY, int z);
}