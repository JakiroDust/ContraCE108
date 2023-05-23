#include "StageEventHandler_Base.h"
#include "Scene_Battle.h"
#include "ScreenManager.h"

void StageEventHandler_Base::Set_Camera_Focus_Player()
{
    if (_toggleFreeCam)
        return;
	float camPosX = 0;
    float camPosY = 0;
    Game_Screen* cam = ScreenManager::GetInstance()->Screen();
    _srcScene->p1()->GetCenterPoint(camPosX, camPosY);
    cam->SetCenterPoint(camPosX, camPosY);
    //cam->focusToPoint(camPosX, camPosY);
}

void StageEventHandler_Base::Debug_KeyDownEventHandler(int KeyCode)
{
    if (STAGE_DEBUG_ALLOW)
    {
        switch (KeyCode)
        {
        case DIK_1:
            _srcScene->p1()->ChangeWeapon(new Equip_Gun_N());
            break;
        case DIK_2:
            _srcScene->p1()->ChangeWeapon(new Equip_Gun_R());
            break;
        case DIK_3:
            _srcScene->p1()->ChangeWeapon(new Equip_Gun_S());
            break;
        case DIK_4:
            _srcScene->p1()->ChangeWeapon(new Equip_Gun_L());
            break;
        case DIK_5:
            _srcScene->p1()->ChangeWeapon(new Equip_Gun_F());
            break;
        case DIK_6:
            break;
        case DIK_7:
            CompleteStage();
            break;
        case DIK_8:
            _toggleFreeCam = true;
            break;
        case DIK_9:
            _toggleFreeCam = false;
            break;
        case DIK_W:
            if (_toggleFreeCam)
            {
                Game_Screen* screen = ScreenManager::GetInstance()->Screen();
                screen->SetPosition(screen->x(), screen->y() + 32);
            }
            break;
        case DIK_S:
            if (_toggleFreeCam)
            {
                Game_Screen* screen = ScreenManager::GetInstance()->Screen();
                screen->SetPosition(screen->x(), screen->y() - 32);
            }
            break;
        case DIK_A:
            if (_toggleFreeCam)
            {
                Game_Screen* screen = ScreenManager::GetInstance()->Screen();
                screen->SetPosition(screen->x() - 32, screen->y());
            }
            break;
        case DIK_D:
            if (_toggleFreeCam)
            {
                Game_Screen* screen = ScreenManager::GetInstance()->Screen();
                screen->SetPosition(screen->x() + 32, screen->y());
            }
            break;
        }
    }
}

void StageEventHandler_Base::KeyDownEventHandler(int KeyCode)
{
    Debug_KeyDownEventHandler(KeyCode);
}