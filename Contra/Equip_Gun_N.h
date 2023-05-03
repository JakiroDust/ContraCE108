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
			_FireRate = 120;
			_reloadTime = 240;
			_maxAmmo = 5;
			_ammo = _maxAmmo;
		}

		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override;
		void Fire(float& x, float& y, int DIR) override;
};

