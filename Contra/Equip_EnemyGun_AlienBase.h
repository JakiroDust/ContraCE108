#pragma once
#include "Equip_EnemyGun_N.h"
class Equip_EnemyGun_AlienBase : public Equip_EnemyGun_N
{
	private:
	public:
		Equip_EnemyGun_AlienBase()
		{
			_isAuto = false;
			_FireRate = 0;
			_reloadTime = 0;
			_maxAmmo = 0;
		}

		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override;
		void Fire(float& x, float& y, int DIR) override;
};

