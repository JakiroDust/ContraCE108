#pragma once
#include "Scene_Base.h"
class Scene_Start :
    public Scene_Base
{
    void KeyDownEventHandler(int KeyCode) override;
    void init();
};

