#pragma once
#include "Game_UpgradeBase.h"
class Game_Upgrade_M :
    public Game_UpgradeBase
{
protected:

public:
    Game_Upgrade_M(float x, float y) : Game_UpgradeBase(x, y) { _SpriteId = ANI_UPGRADE_M; _ghost = true; };
    void applyUpgrade() override;
    
};
class Game_Upgrade_B :
    public Game_UpgradeBase
{
protected:

public:
    Game_Upgrade_B(float x, float y) : Game_UpgradeBase(x, y) { _SpriteId = ANI_UPGRADE_B; _ghost = true; };
    void applyUpgrade() override;

};
class Game_Upgrade_F :
    public Game_UpgradeBase
{
protected:

public:
    Game_Upgrade_F(float x, float y) : Game_UpgradeBase(x, y) { _SpriteId = ANI_UPGRADE_F; _ghost = true; };
    void applyUpgrade() override;

};
class Game_Upgrade_S :
    public Game_UpgradeBase
{
protected:

public:
    Game_Upgrade_S(float x, float y) : Game_UpgradeBase(x, y) { _SpriteId = ANI_UPGRADE_S; _ghost = true; };
    void applyUpgrade() override;

};
class Game_Upgrade_L :
    public Game_UpgradeBase
{
protected:

public:
    Game_Upgrade_L(float x, float y) : Game_UpgradeBase(x, y) { _SpriteId = ANI_UPGRADE_L; _ghost = true; };
    void applyUpgrade() override;

};
class Game_Upgrade_R :
    public Game_UpgradeBase
{
protected:

public:
    Game_Upgrade_R(float x, float y) : Game_UpgradeBase(x, y) { _SpriteId = ANI_UPGRADE_R; _ghost = true; };
    void applyUpgrade() override;

};

namespace UPGRADE
{

#define UP_L 11
#define UP_B 1
#define UP_F 5
#define UP_S 18
#define UP_M 12
#define UP_R 17
    void spawnUpgradeIcon(int ICONTYPE, float x, float y);
}