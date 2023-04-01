#pragma once
#include "GameObject.h"
class CGameCharacter :
    public CGameObject
{
protected:
    int untouchable;
    ULONGLONG untouchable_start;
public:
    CGameCharacter(float x, float y) :CGameObject(x, y) { untouchable = 0; untouchable_start = -1; };
    ~CGameCharacter() {};
};

