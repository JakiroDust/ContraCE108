#pragma once
#include "Game_UpgradeBoxBase.h"
class Game_UpgradeBoxFlying :
    public Game_UpgradeBoxBase
{
    float start_x, start_y;
    DWORD start_dt;
public:
    Game_UpgradeBoxFlying(float _x, float _y, int _type);
    void Update(DWORD dt) override;
    int baseType() override { return TYPE_MOVABLE; }
    void Render() override;
    void Execute_BeforeDelete()override{CreateDieAnimation(ANI_EXPLOSION_ARMY);}
};

class Game_UpgradeBoxStation :
    public Game_UpgradeBoxBase
{
    bool _WindUp = true;
public:
    Game_UpgradeBoxStation(float _x, float _y, int _type);
    void Render() override;
    void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
    int CharID() override { return UP_BOX_STATION; };
    int baseType() override { return TYPE_STATIC; }
    void Execute_BeforeDelete()override { CreateDieAnimation(ANI_EXPLOSION_ARMY); }
};

