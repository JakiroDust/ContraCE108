#pragma once
class Equip_GunBase
{
protected:
	bool _isAuto;
public:
	Equip_GunBase() { _isAuto = false; };
	void spawnBullet(float& x, float& y, float& vx, float& vy) {};
};

