#include "Equip_GunBase.h"
#include "GameManager.h"
float* Equip_GunBase::modifier = &(GameManager::GetInstance()->Speed_Upgrade());

DWORD Equip_GunBase::FireRate()
{
	if (_maxAmmo <= 0)
		return DWORD(_FireRate / (*modifier));
	if (_ammo > 1)
	{
		_ammo--;
		return DWORD(_FireRate / (*modifier));
	}
	else
	{
		_ammo = _maxAmmo;
		return DWORD(_reloadTime / (*modifier));
	}
}