#pragma once
#include "Game_SpecialObject.h"

#define BASEDOOR_WIDTH 24
#define BASEDOOR_HEIGHT 24

class Enemy_Base_Door : public Game_SpecialObject
{
    public:
        Enemy_Base_Door(float x, float y, int z) : Game_SpecialObject(x, y, z, BASEDOOR_WIDTH, BASEDOOR_HEIGHT)
        {
            _moveSpd = 0;
            _DieDelay = 50;
            _gravity = false;
            _HardBody = true;
            _faceLeft = true;
            _haveStandby = false;
            _hp = 30;

        }
        int CharID() override;
        int EnemyType() override { return ENEMY_CONSTRUCTION; }
        void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
        int  getSFXexplodeID() override;
        void Execute_DieAction() override;
        int getSFXCHANNEL() override;
        void Execute_BeforeDelete() override;
        virtual int RewardScore() override { return 1000; };
        int getSFXhitedID() override
        {
            return 40;
        }

};

