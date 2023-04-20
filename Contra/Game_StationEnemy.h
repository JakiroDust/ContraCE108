#pragma once
#include "Game_Enemy.h"
class Game_StationEnemy :
    public Game_Enemy
{
    int baseType() override { return TYPE_STATIC; }
};

