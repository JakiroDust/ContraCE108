#include "Game_Upgrade.h"
#include "Equip_Gun_R.h"
#include "Scene_Battle.h"
#include "GameManager.h"

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
	GameManager::GetInstance()->add_Speed_Upgrade();
}


void UPGRADE::spawnUpgradeIcon(int ICONTYPE, float x, float y)
{
	if (ICONTYPE >= 97)
		ICONTYPE -= 97;
	if (ICONTYPE >= 65)
		ICONTYPE -= 65;
	Game_UpgradeBase* rtn=NULL;
	switch (ICONTYPE)
	{
	case UP_B: rtn = new Game_Upgrade_B(x, y); break;
	case UP_F:rtn = new Game_Upgrade_F(x, y); break;
	case UP_L:rtn = new Game_Upgrade_L(x, y); break;
	case UP_R:rtn = new Game_Upgrade_R(x, y); break;
	case UP_M:rtn = new Game_Upgrade_M(x, y); break;
	case UP_S:rtn = new Game_Upgrade_S(x, y); break;
	default:rtn = new Game_Upgrade_M(x, y); break;
	}
	unique_ptr<Game_ObjectBase> _rtn(rtn);
	Scene_Battle::GetInstance()->add_object(move(_rtn));
}