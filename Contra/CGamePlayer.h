#pragma once
#include "CGameCharacter.h"
class CGamePlayer :
    public CGameCharacter,public GravityHandlerOn
{
public:
    CGamePlayer(float x, float y) :CGameCharacter(x, y),GravityHandlerOn()
    {

    };
};

