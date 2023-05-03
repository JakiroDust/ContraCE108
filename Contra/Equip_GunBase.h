#pragma once

using namespace std;
#include "debug.h"

#define GUN_SPAWNMODE_VECTOR 0
#define GUN_SPAWNMODE_TARGETPOS 1

class Equip_GunBase
{
	protected:
		bool _isAuto = false;
		DWORD _reloadTime = 0;
		DWORD _ammo = 0;
		DWORD _maxAmmo = 0;
		DWORD _FireRate = 0;
	public:
		Equip_GunBase() { _isAuto = false; }
		bool IsAuto() { return _isAuto; }
		virtual DWORD FireRate()
		{
			if (_maxAmmo <= 0)
				return _FireRate;

			if (_ammo > 0)
			{
				_ammo--;
				return _FireRate;
			}
			else
			{
				_ammo = _maxAmmo;
				return _reloadTime;
			}
		}
		virtual void Fire(float& x, float& y, float& vx, float& vy, bool type = false) {}
		virtual void Fire(float& x, float& y, int DIR) {}
};

