#pragma once
#include "Game_Enemy.h"
class Game_StationEnemy : public Game_Enemy
{
public:
    Game_StationEnemy(float x, float y, int z, int width, int height) : Game_Enemy(x, y, z, width, height)
    {
        _moveSpd = 0;
    }
    int baseType() { return TYPE_MOVABLE; }

    void Execute_DieAction() override { Game_Enemy::Execute_DieAction(); }
};

