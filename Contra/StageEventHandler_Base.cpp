#include "StageEventHandler_Base.h"
#include "Scene_Battle.h"
#include "ScreenManager.h"

void StageEventHandler_Base::Set_Camera_Focus_Player()
{
	float camPosX = 0;
    float camPosY = 0;
    Game_Screen* cam = ScreenManager::GetInstance()->Screen();
    _srcScene->p1()->GetCenterPoint(camPosX, camPosY);
    cam->focusToPoint(camPosX, camPosY);
}