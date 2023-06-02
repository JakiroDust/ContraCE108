#pragma once
#include "Game_UpgradeBase.h"
class Game_Upgrade_M :
    public Game_UpgradeBase
{
protected:

public:
    Game_Upgrade_M(float x, float y, int z, int width, int height) : Game_UpgradeBase(x, y, z, width, height) { _SpriteId = ANI_UPGRADE_M; _ghost = true; };
    void applyUpgrade() override;
    
};
class Game_Upgrade_B :
    public Game_UpgradeBase
{
protected:

public:
    Game_Upgrade_B(float x, float y, int z, int width, int height) : Game_UpgradeBase(x, y, z, width, height) { _SpriteId = ANI_UPGRADE_B; _ghost = true; };
    void applyUpgrade() override;

};

class Game_Upgrade_F :
    public Game_UpgradeBase
{
protected:

public:
    Game_Upgrade_F(float x, float y, int z, int width, int height) : Game_UpgradeBase(x, y, z, width, height) { _SpriteId = ANI_UPGRADE_F; _ghost = true; };
    void applyUpgrade() override;

};
class Game_Upgrade_S :
    public Game_UpgradeBase
{
protected:

public:
    Game_Upgrade_S(float x, float y, int z, int width, int height) : Game_UpgradeBase(x, y, z, width, height) { _SpriteId = ANI_UPGRADE_S; _ghost = true; };
    void applyUpgrade() override;

};
class Game_Upgrade_L :
    public Game_UpgradeBase
{
protected:

public:
    Game_Upgrade_L(float x, float y, int z, int width, int height) : Game_UpgradeBase(x, y, z, width, height) { _SpriteId = ANI_UPGRADE_L; _ghost = true; };
    void applyUpgrade() override;

};
class Game_Upgrade_R :
    public Game_UpgradeBase
{
protected:

public:
    Game_Upgrade_R(float x, float y, int z, int width, int height) : Game_UpgradeBase(x, y, z, width, height) { _SpriteId = ANI_UPGRADE_R; _ghost = true; };
    void applyUpgrade() override;

};
