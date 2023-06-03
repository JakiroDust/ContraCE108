#pragma once
#include "Game_SpecialObject.h"
class Game_UpgradeBoxBase :
    public Game_SpecialObject
{
private:
    int type;
public:
    Game_UpgradeBoxBase(float x, float y, int z , int width, int height,int _type);
    void OnCollisionWith(PCOLLISIONEVENT e) override;
    void Execute_DieAction() override;
    int RewardScore() override;
    void Execute_BeforeDelete() override {};
    void Update(DWORD dt) override {};
    void Update(DWORD dt, vector<Game_ObjectBase*>* coObjects) override;

};

