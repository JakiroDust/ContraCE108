#include "Scene_Battle.h"
#include "ScreenManager.h"
#include "Game_KeyInput.h"
#include "Game_Platform.h"
#include "Enemy_RedGunner.h"
#include "Enemy_Infary.h"
#include "Game_Bullet.h"
#include "Enemy_Sniper.h"
#include "Spawner_Infary_Stage1.h"
#include <fstream>
using namespace std;
#define MAP_TEXU_WIDTH 16
#define MAP_TEXU_HEIGHT 8
float BG_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

Scene_Battle::~Scene_Battle()
{
    //delete _p1;
    //delete _p2;

    //for (int i = 0; i < _layers.size(); i++)
    //{
    //    delete  _layers.at(i);
    //}
    //_layers.clear();

    /*  for (int i = 0; i < _objects.size(); i++)
    {
        delete  _objects.at(i);
    }
    _objects.clear();*/
    //_delete_spatial();
    //__objects.clear();
    Unload();
}

void Scene_Battle::Render()
{
    Game_Screen* screen = ScreenManager::GetInstance()->Screen();

    vector<Game_ObjectBase*> RenderQueue;
    // layers
    for (int i = 0; i < _layers.size(); i++)
    {
        Game_ObjectBase* obj = _layers[i].get();
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
    vector<int> id_list = screen->Get_ObjectsID_InsideScreen(spatial, GET_OBJECTS_RANGE);
    for (auto&i :id_list)
    {
        Game_ObjectBase* obj = __objects[i].get();
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

    CGame::GetInstance()->GetDirect3DDevice()->ClearRenderTargetView(CGame::GetInstance()->GetRenderTargetView(), BG_color);
    float x, y;
    ScreenManager::GetInstance()->Screen()->GetCenterPoint(x, y);
    renderBG(x, y);
    for (int i = 0; i < RenderQueue.size(); i++)
    {
        RenderQueue[i]->Render();
    }
    // images

    // Render Images

}

void Scene_Battle::Update(DWORD dt)
{
    dt = min(dt, 40);

    if (!_isPlaying)
        return;

    Game_Screen* screen = ScreenManager::GetInstance()->Screen();

    // Event Handler
    if (_controller != NULL)
        _controller->Update(dt);

    // Map Update
    for (int i = 0; i < _layers.size(); i++)
    {
        Game_ObjectBase* obj = _layers[i].get();
        screen->CheckObjectIfNeedRender(obj);
    }

    if (__objects.empty())
        return;

    vector<int> id_list= screen->Get_ObjectsID_InsideScreen(spatial, GET_OBJECTS_RANGE);
    vector<PGAMEOBJECT>* nearbyObject = getObjectById(id_list);
    //for (int i = 0; i < _objects.size(); i++)
    //float old_l, old_right, old_bottom, old_top,
    float   new_l, new_right, new_bottom, new_top;

    //vector<Game_ObjectBase*>* colObjects = objects();

    for(auto& i : id_list)
    {
        Game_ObjectBase* obj = __objects[i].get();
        //obj->Update(dt);


        if (obj->baseType() == TYPE_STATIC)
        {
            if (obj->NeedScanCollision())
                obj->Update(dt, nearbyObject);
            else
                obj->Update(dt);

        }
        else {


            if (obj->NeedScanCollision())
                obj->Update(dt, nearbyObject);
            else
                obj->Update(dt);
            obj->GetLTRB(new_l, new_top, new_right, new_bottom);
            spatial->update(i,(int)new_l, (int)new_bottom, (int)new_right, (int)new_top);
           
        }
        screen->CheckObjectIfNeedRender(obj);
    }

    // Terminate objects have Delete flag
    for (auto& i : id_list)
    {
        Game_ObjectBase* obj = __objects[i].get();
        if (obj->IsDeleted())
        {
            DebugOut(L"deleted id=%d\n", i);
            delete_object(i);
        }
    }
    nearbyObject->clear();
    delete nearbyObject;
}

void Scene_Battle::Load()
{
    if (_controller == NULL)
    {
        DebugOut(L"[LOAD FAILED] Can't find Stage controller.\n");
        return;
    }
    _controller->Load();

}

void Scene_Battle::Unload()
{
    _delete_spatial();
    map_sprite.clear();
    __objects.clear();
    _p1.reset(NULL);
    //_p2.reset(NULL);
    if (_controller != NULL)
        delete _controller;
}

void Scene_Battle::KeyDownEventHandler(int KeyCode)
{
    if (_controller != NULL)
    {
        _controller->KeyDownEventHandler(KeyCode);
    }
}

//=====================================================================================================================



//void Scene_Battle::checkObjectNeedRender(Game_ObjectBase* obj)
//{
//    float y, x;
//    
//    Game_Screen* screen = ScreenManager::GetInstance()->Screen();
//    screen->GetCenterPoint(x, y);
//    //getNearByIDyx(y, x);
//    if (obj->x() + obj->width() < screen->x()
//        || obj->x() > screen->x() + screen->width()
//        || obj->y() < screen->y() - screen->height()
//        || obj->y() - obj->height() > screen->y())
//    {
//        obj->SetNeedRender(false);
//        if (dynamic_cast<Game_Bullet*>(obj))
//        {
//            obj->DeleteThis();
//        }
//    }
//    else {
//        obj->SetNeedRender(true);
//    }
//}

//=====================================================================================================================
// DEMO
void Scene_Battle::addPlayer1()
{
    _p1_id = add_object(move(_p1));
    Game_KeyInput::GetInstance()->AddObjectControl(p1());
}
/*
void Scene_Battle::addPlayer2()
{
    _p2_id = add_object(move(_p2));
    Game_KeyInput::GetInstance()->AddObjectControl(p2());
}*/


//void Scene_Battle::Create_Stage_Demo()
//{
//    _controller = new StageEventHandler_S1(this);
//
//    _mapWidth = 3328;
//    _mapHeight = GAMESCREEN_HEIGHT;
//    ScreenManager::GetInstance()->Screen()->SetViewBox(_mapWidth, _mapHeight);
//    _init_spatial();
//    _ParseSection_DICT("textures\\MAP1");
//
//    _p1.reset(new Game_Player(40.0f, _mapHeight - 40.0f, 2));
//
//    addPlayer1();
//    SoundSystem* SS = SoundSystem::getInstance();
//    SS->playBGM(BGM_JUNGLE);
//    //unique_ptr<Obj_ContraBot> bot (new Obj_ContraBot(80.0f, _mapHeight - 40.0f + 32, 2)); add_object(move(bot));
//    //unique_ptr<Obj_SmartBot>smartbot(new Obj_SmartBot(100.0f, _mapHeight - 40.0f + 32, 2)); add_object(move(smartbot));
//    
//    unique_ptr<Enemy_Sniper> sniper(new Enemy_Sniper(300.0f, _mapHeight - 150.0f, 2)); add_object(move(sniper));
//    /*
//    unique_ptr<Game_Blocker> block1 ( new Game_Blocker(-18.0f, _mapHeight - 20.0f, 1, 20, GAMESCREEN_HEIGHT - 20));
//    unique_ptr<Game_Blocker> block2 ( new Game_Blocker(_mapWidth - 20.0f, _mapHeight - 20.0f, 1, 20, GAMESCREEN_HEIGHT - 20));
//
//    unique_ptr<Game_Water> water1(new Game_Water(0.0f, 20.0f, 1, 288, 20));
//    unique_ptr<Game_Water> water2(new Game_Water(352.0f, 20.0f, 1, 2976, 20));
//
//    unique_ptr<Game_Platform> plat1(new Game_Platform(160.0f, _mapHeight - 150.0f, 1, 96, 10));
//    unique_ptr<Game_Platform> plat2(new Game_Platform(256.0f, _mapHeight - 178.0f, 1, 32, 10));
//    unique_ptr<Game_Platform> plat3(new Game_Platform(352.0f, _mapHeight - 178.0f, 1, 32, 10));
//    unique_ptr<Game_Platform> plat4(new Game_Platform(416.0f, _mapHeight - 150.0f, 1, 64, 10));
//    unique_ptr<Game_Blocker> plat5(new Game_Blocker(288.0f, _mapHeight - 215.0f, 1, 64, 32));
//    unique_ptr<Game_Platform> plat6(new Game_Platform(32.0f, _mapHeight - 118.0f, 1, 736, 10));
//
//    //Demo_Layer* demo = new Demo_Layer(0, 0, 0, 3328, 240);
//    //
//    add_object(move(water1));//1
//    add_object(move(water2));//2
//    add_object(move(block1));//3
//    add_object(move(block2));//4
//    add_object(move(plat1));//5
//    add_object(move(plat2));//6
//    add_object(move(plat3));//7
//    add_object(move(plat4));//8
//    add_object(move(plat5));//9
//    add_object(move(plat6));//10
//    */
//    _ParseOBject("textures\\MAP1");
//    //_layers.push_back(demo);
//    ScreenManager::GetInstance()->Screen()->focusToPoint(GAMESCREEN_WIDTH/2.0f,GAMESCREEN_HEIGHT/2.0f, _mapWidth, _mapHeight);
//    
//}

int Scene_Battle::add_object(unique_ptr<Game_ObjectBase>&& object)
{
    //_objects.push_back(object);
    int id = id_nth;
    if (!id_recycle_bin.empty())
    {
        id = id_recycle_bin[id_recycle_bin.size() - 1];
        id_recycle_bin.pop_back();
    }
    else
    {
        id_nth++;
    }
    float l, t, r, b;
    object->SetId(id);
    object->GetLTRB(l, t, r, b);
    __objects[id] =move(object);
    
 
    
   // DebugOut(L"id %d l=%d t=%d r=%d b=%d\n", id_nth, l, t, r, b);
    spatial->insert(id, l, b, r, t);
    return id;
    

}

/*void Scene_Battle::delete_object(unique_ptr<Game_ObjectBase>& object)
{
    int id = object->id();
    float left, top, right, bottom;
    object->GetLTRB(left, top, right, bottom);
    spatial->del_object(id, left, top, right, bottom);
    __objects.erase(id);
    id_recycle_bin.push_back(id);
}
*/
void Scene_Battle::delete_object(int id)
{
    Game_ObjectBase* object = __objects[id].get();
    float left, top, right, bottom;
    object->GetLTRB(left, top, right, bottom);
    spatial->remove(id);
    __objects[id].reset();
    __objects.erase(id);
    id_recycle_bin.push_back(id);
}

void Scene_Battle::_init_spatial()
{
    int width = int(GAMESCREEN_WIDTH * 1.1),
        height= int(GAMESCREEN_HEIGHT*1.1),
        n= _mapHeight / width+1,
        m= _mapWidth/ height+1;
    if (spatial != NULL)
        delete spatial;
    spatial = new QuadTree(0, 0, width, height,8,5);




}



/// REMBER TO DELETE AFTER USE
vector<Game_ObjectBase*>* Scene_Battle::getObjectById(vector<int>& vtr)
{
    vector<Game_ObjectBase*>* objects= new vector<Game_ObjectBase*>;
    for (auto& id : vtr)
    {
        objects->push_back(__objects[id].get());
    }
    return objects;
}
void Scene_Battle::_delete_spatial()
{
    delete spatial;
}


///PROTYPE

//=====================================================================================================
// PARSE

void Scene_Battle::parseMap(string line)
{
    PAUSE();
    _ParseSection_DICT(line);
    _ParseOBject(line);
    PLAY();
}

void Scene_Battle::_ParseSection_DICT(string line)
{
    map_sprite.clear();
    //texu
    int n = int(_mapHeight / MAP_TEXU_HEIGHT),
        m = int(_mapWidth / MAP_TEXU_WIDTH);
    if (mapTexSpatial != NULL)
        delete mapTexSpatial;
    mapTexSpatial = new SpatialforTex(n, m, MAP_TEXU_WIDTH, MAP_TEXU_HEIGHT, int(340 / MAP_TEXU_HEIGHT), int(340 / MAP_TEXU_WIDTH));
    ifstream f;
    f.open(line + "\\info.txt");


    if (f.is_open())
    {
        f >> map_id;
        width = MapWidth() / MAP_TEXU_WIDTH;
        height = MapHeight() / MAP_TEXU_HEIGHT;
    }
    else
    {
        // handle error if the file cannot be opened
        // set default values or throw an exception
        DebugOut(L"CANNOT READ %s\\info.txt", line);
        return;
    }
    f.close();
    f.open(line + "\\mapping.txt");
    set<int> dect;
    if (f.is_open())
    {
        int count = 0;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int temp;
                f >> temp;
                map[i][j] = temp;
                dect.insert(temp);
                count++;
                if (count == 600)
                {

                }
            }
        }
        wstring path = ToWSTR(line + "\\merged.png");
        _map_tex = CGame::GetInstance()->LoadTexture(path.c_str(), false);
        for (auto& i : dect)
        {
            int texID = i;
            int index_value = i;
            int left = 0 + MAP_TEXU_WIDTH * (index_value % 10),
                top = 0 + MAP_TEXU_HEIGHT * (index_value / 10),
                right = left+ MAP_TEXU_WIDTH-1,
                bottom = top+MAP_TEXU_HEIGHT-1;
            map_sprite[texID].reset(new CSprite(texID, left, top, right, bottom, _map_tex));
        }
    }
    else
    {
        DebugOut(L"CANNOT READ %s\\mapping.txt", line);
        return;
    }
    f.close();

    int curID = 0;
    int curN = 0, curM = 0;
    //parsing texture+
    curN = 0, curM = 0;
    curID = 0;
    int a = MapHeight();
    DebugOut(L"%d\n",a);
    for (curN = 0; curN < height; curN++)
    {
        for (curM = 0; curM < width; curM++)
        {

             addMapPart(curID,(curM)*MAP_TEXU_WIDTH,MapHeight() - curN * MAP_TEXU_HEIGHT- MAP_TEXU_HEIGHT);
                curID++;
        }
    }


}
void Scene_Battle::_ParseOBject(string line)
{
    fstream f;
    f.open(line+"\\object.txt");
    if (f.is_open())
    {
        int16_t id;
        float x, y;
        int width, height;
        unique_ptr<Game_ObjectBase>obj;
        while (!f.eof() || !f.fail())
        {
            try
            {
                f >> id >> x >> y >> width >> height;
                
                switch (id)
                {
                // PARSE TERRAIN
                case TBLOCKER: obj.reset(new Game_Blocker(x, y, Z_INDEX_TERRAIN, width, height));
                    break;
                case TPLATFORM: obj.reset(new Game_Platform(x, y, Z_INDEX_TERRAIN, width, height));
                    break;
                case TWATER: obj.reset(new Game_Water(x, y, Z_INDEX_TERRAIN, width, height));
                    break;
                case TDEADLY: obj.reset(new Game_DeadlyBlock(x, y, Z_INDEX_TERRAIN, width, height));
                    break;

                // PARSE OBJECT
                case CHAR_CONTRA:
                    _p1.reset(new Game_Player(x, y, Z_INDEX_PLAYER));
                    addPlayer1();
                    obj.reset(NULL);
                    break;
                case SNIPER: obj.reset(new Enemy_Sniper(x, y, Z_INDEX_ENEMY));
                    break;
                case CAMERA:
                    ScreenManager::GetInstance()->Screen()->SetPosition(x, y);
                    obj.reset(NULL);
                    break;

                // SPAWNER
                case SPAWNER_INFARY: obj.reset(new Spawner_Infary_Stage1(x, y, Z_INDEX_TERRAIN, width));
                    break;

                default:
                    obj.reset(NULL);
                    DebugOut(L"Unknown id=%d", id);
                    break;
                }
                if (obj.get() != NULL)
                {
                    add_object(move(obj));
                }
            }
            catch(...)
            {
                DebugOut(L"PLEASE RECHECK THE OBJECT.TXT IN MAP DIC");
                return;
            }

        }
    }
    else
    {
        DebugOut(L"CANNOT READ %s\\object.txt", line);
        return;
    }
    f.close();

}

void Scene_Battle::renderBG(float x, float y)
{
    vector<int> id = mapTexSpatial->getNearByIDyx(y, x);
    for (int i = 0; i < id.size(); i++)
    {
        int n = id[i] / width,
            m=id[i]%width;
        int _x, _y;
        mapTexSpatial->getXYCenter(id[i], _x, _y);
        map_sprite[map[n][m]].get()->Draw(_x,_y);
    }
}
void Scene_Battle::renderBG(int& x, int& y)
{
    renderBG(x / 1.0f, y / 1.0f);
}
void Scene_Battle::addMapPart( int partID, int x, int y)
{
    mapTexSpatial->init_object_ONLYONCE(partID, x, y );
}

//vector<int> Scene_Battle::getNearbyIDFast()
//{
//    float x, y;
//    ScreenManager::GetInstance()->Screen()->GetCenterPoint(x, y);
//    int width =(int) (GAMESCREEN_WIDTH * 1.3),
//        height = (int)(GAMESCREEN_HEIGHT * 1.3);
//    return getNearByIDwithWH(x, y, width, height);
//}

vector<int> Scene_Battle::getNearByID(int left, int bottom, int right, int top)
{
    return spatial->search(left, bottom, right, top, -100);
}

vector<int> Scene_Battle::getNearByIDwithWH(int x, int y, int width, int height)
{
    int left = x - width / 2,
        right = left + width,
        bottom = y - height / 2,
        top = y + height;
    return spatial->search(left, bottom, right, top,-100);
}

