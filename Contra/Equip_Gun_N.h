#pragma once

using namespace std;

#include "Equip_GunBase.h"
#include "Obj_Bullet_N.h"

class Equip_Gun_N : public Equip_GunBase
{
	private:

	public:
		Equip_Gun_N() { _isAuto = false; }

		void Fire(float& x, float& y, float& vx, float& vy, bool type = false) override;
		void Fire(float& x, float& y, int DIR) override;
};

