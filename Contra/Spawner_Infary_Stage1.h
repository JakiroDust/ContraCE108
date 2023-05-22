#pragma once
#include "Game_Spawner.h"

#define SPAWNER_INFARY_S1_BASE_INTERVAL 800

class Spawner_Infary_Stage1 : public Game_Spawner
{
	private:
		
	public:
		Spawner_Infary_Stage1(float x, float y, int z, DWORD modifier) : Game_Spawner(x, y, z)
		{
			_Interval = 800 + modifier;
		}

		void Update(DWORD dt);
};
