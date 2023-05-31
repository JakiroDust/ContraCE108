#pragma once
#include "Equip_GunBase.h"
#include "Obj_Bullet_F.h"

class Equip_Gun_F : public Equip_GunBase
{
	private:
	public:
		Equip_Gun_F()
		{
			_isAuto = false;
			_FireRate = 250;
		}

		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override;
		void Fire(float& x, float& y, int DIR) override;
};

