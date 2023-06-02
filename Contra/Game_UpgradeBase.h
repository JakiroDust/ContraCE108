#pragma once
#include "Game_SpecialObject.h"

class Game_UpgradeBase :
    public Game_SpecialObject
{
public:
    Game_UpgradeBase(float x, float y, int z, int width, int height) : Game_SpecialObject(x, y, z, width, height) {};
    virtual void applyUpgrade() {};
    void OnCollisionWith(PCOLLISIONEVENT e) override;
    void Render() override;
};

