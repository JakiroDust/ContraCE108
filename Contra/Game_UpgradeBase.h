#pragma once
#include "Game_SpecialObject.h"
namespace UPGRADE
{
#define UPGRADE_ICON_LENGTH 23
#define UPGRADE_ICON_HEIGHT 12
}
using namespace UPGRADE;
class Game_UpgradeBase :
    public Game_SpecialObject
{
public:
    Game_UpgradeBase(float x, float y, int z=2, int width= UPGRADE_ICON_LENGTH, int height= UPGRADE_ICON_HEIGHT);
    virtual void applyUpgrade() {};
    void OnCollisionWith(PCOLLISIONEVENT e) override;
    void Render() override;
};

