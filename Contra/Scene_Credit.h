#pragma once
#include "Scene_Base.h"
class Scene_Credit :
    public Scene_Base
{
    void init();
    bool startTimer = false;
    DWORD _waitingTick = 24000;
public:
    Scene_Credit() : Scene_Base() {};
    void KeyDownEventHandler(int KeyCode) override;
    void Update(DWORD dt) override;
    // void Render() override;
    void Load() override;
    void Unload() override;
    void nextScene() override;
    ~Scene_Credit() { Unload(); };
};

