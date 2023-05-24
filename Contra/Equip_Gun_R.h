#pragma once
#include "Equip_GunBase.h"
class Equip_Gun_R : public Equip_GunBase
{
	private:
	public:
		Equip_Gun_R()
		{
			_isAuto = true;
			_FireRate = 120;
			_reloadTime = 0;
			_maxAmmo = 0;
			_ammo = _maxAmmo;

		}

		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override;
		void Fire(float& x, float& y, int DIR) override;
};

