#pragma once
#include "Game_Picture.h"
#include "debug.h"
#include "Animations.h"
class Game_Picture_Static :
    public Game_Picture
{
    float _ratio;
public:
    Game_Picture_Static(float screenX, float screenY, int z, int spriteID,float ratio=1, BYTE RenderMode = RENDER_MODE_TOP_LEFT);
    void Render() override;
};

