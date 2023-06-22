#pragma once
#include "Game_Terrain.h"

#define BOSSBASE_CELL_WIDTH 32
#define BOSSBASE_CELL_HEIGHT 32
#define BOSSBASE_HALFCELL_HEIGHT 16
#define BOSSBASE_EXPLOSION_INTERVAL 600

// Can explode after boss die
class Obj_BossBase_S1 : public Game_Terrain
{
	private:
		int _triggerID = 0;
		DWORD _explosionOffset = 0;
		DWORD _explosionTick = 0;
		bool _explosionTrigger = false;
		bool _finishExplosion = false;
		void StartExplosion();
	public:
		Obj_BossBase_S1(float x, float y, int z, DWORD TimeOffset) : Game_Terrain(x, y, z, BOSSBASE_CELL_WIDTH, BOSSBASE_CELL_HEIGHT)
		{
			_explosionOffset = TimeOffset;
			_SpriteId = ANI_BLACK_BOX;
		}
		bool IsBlocking() { return 1; }
		bool BlockingCondition(DWORD dt, PCOLLISIONEVENT e) override;
		void Update(DWORD dt) override;
		void Render() override;
		void TriggerExplosion();
};

class Obj_BossBase_S1_half : public Obj_BossBase_S1
{
private:
	int _triggerID = 0;
	DWORD _explosionOffset = 0;
	DWORD _explosionTick = 0;
	bool _explosionTrigger = false;
	bool _finishExplosion = false;
	void StartExplosion();
public:
	Obj_BossBase_S1_half(float x, float y, int z, DWORD TimeOffset) : Obj_BossBase_S1(x, y, z, TimeOffset)
	{
		_height = BOSSBASE_HALFCELL_HEIGHT;
		_SpriteId = ANI_BLACK_BOX_32_16;
	}
};

