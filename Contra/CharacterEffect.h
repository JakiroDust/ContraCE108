#pragma once
#include "CharacterEffect_Base.h"
class CharacterEffect_Barrier :
    public CharacterEffect_Base
{
    CharacterEffect_Barrier(Game_Character* _target, int _duration=0, bool isInfinity=false);
    void start() override;
};

