#pragma once

#include "Equip_GunBase.h"
#include "Obj_Bullet_N.h"

class Equip_Gun_N : public Equip_GunBase
{
	private:
	public:
		Equip_Gun_N()
		{
			_isAuto = false;
			_FireRate = 150;
			_reloadTime = 0;
			_maxAmmo = 0;
			_ammo = _maxAmmo;
		}
		int GunID() override { return GUN_N; }
		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override;
		void Fire(float& x, float& y, int DIR) override;
};

