#pragma once

using namespace std;
#include "debug.h"

#define GUN_SPAWNMODE_VECTOR 0
#define GUN_SPAWNMODE_TARGETPOS 1

class Equip_GunBase
{
	protected:
		bool _isAuto;
		DWORD _FireRate;
	public:
		Equip_GunBase() { _isAuto = false; }
		bool IsAuto() { return _isAuto; }
		DWORD FireRate() { return _FireRate; }
		virtual void Fire(float& x, float& y, float& vx, float& vy, bool type = false) {}
		virtual void Fire(float& x, float& y, int DIR) {}
};

