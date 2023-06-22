#include "Equip_GunBase.h"
#include "MusicManager.h"

DWORD Equip_GunBase::FireRate()
{
	if (_maxAmmo <= 0)
		return _FireRate;
	if (_ammo > 1)
	{
		_ammo--;
		return _FireRate;
	}
	else
	{
		_ammo = _maxAmmo;
		return _reloadTime ;
	}
}

int Equip_GunBase::getShootSFX()
{
	return -1;
}

void Equip_GunBase::playShootSFX()
{
	SoundSystem::getInstance()->playSFX(getShootSFX(), CHANNEL_SFX_CONTRA, 1);
}


