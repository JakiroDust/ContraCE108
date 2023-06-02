#include "Game_Upgrade.h"
#include "Equip_Gun_R.h"
#include "Scene_Battle.h"
void Game_Upgrade_M::applyUpgrade()
{
	Scene_Battle::GetInstance()->p1()->ChangeWeapon(new Equip_Gun_R());
}

void Game_Upgrade_B::applyUpgrade()
{
}

void Game_Upgrade_F::applyUpgrade()
{
	Scene_Battle::GetInstance()->p1()->ChangeWeapon(new Equip_Gun_F());
}

void Game_Upgrade_S::applyUpgrade()
{
	Scene_Battle::GetInstance()->p1()->ChangeWeapon(new Equip_Gun_S());
}

void Game_Upgrade_L::applyUpgrade()
{
	Scene_Battle::GetInstance()->p1()->ChangeWeapon(new Equip_Gun_L());
}
void Game_Upgrade_R::applyUpgrade()
{
}
