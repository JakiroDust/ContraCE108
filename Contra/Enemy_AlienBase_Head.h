#pragma once
#include "Game_SpecialObject.h"
#include "Equip_EnemyGun_AlienBase.h"
#define AB_HEAD_WIDTH 28
#define AB_HEAD_HEIGHT 48

class Enemy_AlienBase_Head : public Game_SpecialObject
{
	private:
        int _BodyID;
	public:
		Enemy_AlienBase_Head(float x, float y, int z, int BodyID) : Game_SpecialObject(x, y, z, AB_HEAD_WIDTH, AB_HEAD_HEIGHT)
		{
            _weapon = new Equip_EnemyGun_AlienBase();
            _moveSpd = 0;
            _DieDelay = 50;
            _gravity = false;
            _HardBody = true;
            _faceLeft = true;
            _ghost = true;
            _haveStandby = false;
            _hp = 40;
            _BodyID = BodyID;
		}
        ~Enemy_AlienBase_Head()
        {
            Cleaning();
        }
        int CharID() override;
        int EnemyType() override { return ENEMY_CONSTRUCTION; }
        void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
        int  getSFXexplodeID() override;
        void Execute_DieAction() override;
        void Execute_BeforeDelete() override;
        virtual int RewardScore() override { return 1000; };
        int getSFXhitedID() override
        {
            return 40;
        }
};

