#include "Scene_Battle.h"
#include "ScreenManager.h"
#include "Game_KeyInput.h"
#include "Game_Platform.h"
#include "Obj_ContraBot.h"

Scene_Battle::~Scene_Battle()
{
    delete _p1;
    delete _p2;

    for (int i = 0; i < _layers.size(); i++)
    {
        delete  _layers.at(i);
    }
    _layers.clear();

  /*  for (int i = 0; i < _objects.size(); i++)
    {
        delete  _objects.at(i);
    }
    _objects.clear();*/
    _delete_spatial();
    __objects.clear();
}

void Scene_Battle::Render()
{
    vector<Game_ObjectBase*> RenderQueue;
    // layers
    for (int i = 0; i < _layers.size(); i++)
    {
        Game_ObjectBase* obj = _layers[i];
        if (obj->NeedRender() == false) {
            continue;
        }
        if (RenderQueue.size() == 0)
        {
            RenderQueue.push_back(obj);
            continue;
        }
        int j = int(RenderQueue.size());
        while (j > 0 && obj->z() < RenderQueue[j-1]->z())
        {
            j--;
        }
        std::vector<Game_ObjectBase*>::iterator it = RenderQueue.begin();
        RenderQueue.insert(it + j, obj);
    }
    // other game objects
    vector<int> id_list = getNearbyIDFast();
    for (auto&i :id_list)
    {
        Game_ObjectBase* obj = __objects[i];
        if (obj->NeedRender() == false) {
            continue;
        }
        if (RenderQueue.size() == 0)
        {
            RenderQueue.push_back(obj);
            continue;
        }
        int j =int( RenderQueue.size());
        while (j > 0 && obj->z() < RenderQueue[j-1]->z())
        {
            j--;
        }
        std::vector<Game_ObjectBase*>::iterator it = RenderQueue.begin();
        RenderQueue.insert(it + j, obj);
    }
    // Render ingame objects
    for (int i = 0; i < RenderQueue.size(); i++)
    {
        RenderQueue[i]->Render();
    }
    // images

    // Render Images
}

void Scene_Battle::Update(DWORD dt)
{
    for (int i = 0; i < _layers.size(); i++)
    {
        Game_ObjectBase* obj = _layers[i];
        checkObjectNeedRender(obj);
    }

    vector<int> id_list= getNearbyIDFast();
    vector<PGAMEOBJECT>* nearbyObject = getObjectById(id_list);
    //for (int i = 0; i < _objects.size(); i++)
    float old_l, old_right, old_bottom, old_top,
        new_l, new_right, new_bottom, new_top;

    //vector<Game_ObjectBase*>* colObjects = objects();

    for(auto& i : id_list)
    {
        Game_ObjectBase* obj = __objects[i];
        //obj->Update(dt);


        if (obj->baseType() == TYPE_STATIC)
        {
            obj->Update(dt, nearbyObject);

        }
        else {

            obj->GetLTRB(old_l, old_top, old_right, old_bottom);
            obj->Update(dt, nearbyObject);
            obj->GetLTRB(new_l, new_top, new_right, new_bottom);
            spatial->update(i, old_l, old_top, old_right, old_bottom, new_l, new_top, new_right, new_bottom);
           
        }
        checkObjectNeedRender(obj);
    }
    delete nearbyObject;
    // Test
    Demo_Camera_Action();
}
vector<int> Scene_Battle::getNearByIDyx(int y, int x)
{
    return spatial->getNearByIDyx(y, x);
}
void Scene_Battle::checkObjectNeedRender(Game_ObjectBase* obj)
{
    float y, x;

    
    Game_Screen* screen = ScreenManager::GetInstance()->Screen();
    screen->GetCenterPoint(x, y);
    getNearByIDyx(y, x);
    if (obj->x() + obj->width() < screen->x()
        || obj->x() > screen->x() + screen->width()
        || obj->y() + obj->height() < screen->y()
        || obj->y() > screen->y() + screen->height())
    {
        obj->SetNeedRender(false);
    }
    else {
        obj->SetNeedRender(true);
    }
}

//=====================================================================================================================
// DEMO
void Scene_Battle::Create_Stage_Demo()
{
    _mapWidth = 3328;
    _mapHeight = GAMESCREEN_HEIGHT;
    _init_spatial();

    _p1 = new Game_Player(40,40,2);
    Obj_ContraBot* bot = new Obj_ContraBot(80, 40, 2);

    Game_Blocker* block1 = new Game_Blocker(-18, 0, 1, 20, GAMESCREEN_HEIGHT - 20);
    Game_Blocker* block2 = new Game_Blocker(_mapWidth - 20, 1, 0, 20, GAMESCREEN_HEIGHT - 20);

    Game_Water* water1 = new Game_Water(0, GAMESCREEN_HEIGHT - 20, 1, 288, 20);
    Game_Water* water2 = new Game_Water(352, GAMESCREEN_HEIGHT - 20, 1, 2976, 20);

    Game_Platform* plat1 = new Game_Platform(160, 150, 1, 96, 10);
    Game_Platform* plat2 = new Game_Platform(256, 178, 1, 32, 10);
    Game_Platform* plat3 = new Game_Platform(352, 178, 1, 32, 10);
    Game_Platform* plat4 = new Game_Platform(416, 150, 1, 64, 10);
    Game_Blocker* plat5 = new Game_Blocker(288, 215, 1, 64, 32);
    Game_Platform* plat6 = new Game_Platform(32, 118, 1, 704, 10);

    Demo_Layer* demo = new Demo_Layer(0, 0, 0, 3328, 239);
    add_object(_p1);//0
    add_object(water1);//1
    add_object(water2);//2
    add_object(block1);//3
    add_object(block2);//4
    add_object(plat1);//5
    add_object(plat2);//6
    add_object(plat3);//7
    add_object(plat4);//8
    add_object(plat5);//9
    add_object(plat6);//10
    add_object(bot);//11
    _layers.push_back(demo);
    ScreenManager::GetInstance()->Screen()->focusToPoint(GAMESCREEN_WIDTH/2,GAMESCREEN_HEIGHT/2, _mapWidth, _mapHeight);
    Game_KeyInput::GetInstance()->AddObjectControl(_p1);
}
void Scene_Battle::add_object(Game_ObjectBase*object)
{
    //_objects.push_back(object);
    __objects[id_nth] = object;
    object->SetId(id_nth);
    float l, t, r, b;
    object->GetLTRB(l, t, r, b);
    DebugOut(L"id %d l=%d t=%d r=%d b=%d\n", id_nth, l, t, r, b);
    spatial->init_object(id_nth, l, t, r, b);
    id_nth++;
    

}
void Scene_Battle::delete_object(Game_ObjectBase* object)
{
    int id = object->id();
    float left, top, right, bottom;
    object->GetLTRB(left, top, right, bottom);
    spatial->del_object(id, left, top, right, bottom);
    __objects.erase(id);
}
void Scene_Battle::delete_object(int id)
{
    delete_object(__objects[id]);
}
void Scene_Battle::_init_spatial()
{
    int width = int(GAMESCREEN_WIDTH * 1.1),
        height= int(GAMESCREEN_HEIGHT*1.1),
        n= _mapHeight / width+1,
        m= _mapWidth/ height+1;
    
    spatial = new Spatial(n, m, width, height);

}

vector<int> Scene_Battle::getNearByID(int n, int m)
{
    return spatial->getNearByID(n, m);
}

vector<int> Scene_Battle::getNearbyIDFast()
{
    float x, y;
    Game_Screen* screen = ScreenManager::GetInstance()->Screen();
    screen->GetCenterPoint(x, y);
    return  getNearByIDyx(y, x);
}

/// REMBER TO DELETE AFTER USE
vector<Game_ObjectBase*>* Scene_Battle::getObjectById(vector<int>& vtr)
{
    vector<Game_ObjectBase*>* objects= new vector<Game_ObjectBase*>;
    for (auto& id : vtr)
    {
        objects->push_back(__objects[id]);
    }
    return objects;
}
void Scene_Battle::_delete_spatial()
{
    delete spatial;
}

int moveRange = 0;
bool switchLeft = false;
float camPosX = 0;
float camPosY = 0;

void Scene_Battle::Demo_Camera_Action()
{
    Game_Screen* cam = ScreenManager::GetInstance()->Screen();
    p1()->GetCenterPoint(camPosX, camPosY);
    cam->focusToPoint(camPosX, camPosY, _mapWidth, _mapHeight);  

    //cam->GetCenterPoint(camPosX, camPosY);
    //if (moveRange > 0)
    //{
    //    moveRange--;
    //    if (switchLeft) {
    //        camPosX--;
    //    }
    //    else {
    //        camPosX++;
    //    }

    //    cam->focusToPoint(camPosX, camPosY, _mapWidth, _mapHeight);
    //}
    //else
    //{
    //    moveRange = _mapWidth / 2;
    //    switchLeft = !switchLeft;
    //}


}

///PROTYPE
