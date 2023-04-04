#include "Scene_Battle.h"

Scene_Battle::~Scene_Battle()
{
    delete _p1;
    delete _p2;

    for (int i = 0; i < _layers->size(); i++)
    {
        delete  _layers->at(i);
    }
    _layers->clear();

    for (int i = 0; i < _objects->size(); i++)
    {
        delete  _objects->at(i);
    }
    _objects->clear();
}

void Scene_Battle::Render()
{
    vector<Game_ObjectBase*>* RenderQueue = new vector<Game_ObjectBase*>();
    // layers
    for (int i = 0; i < _layers->size(); i++)
    {
        Game_ObjectBase* obj = _layers->at(i);
        if (obj->NeedRender() == false) {
            continue;
        }
        RenderQueue->push_back(obj);
        int j = RenderQueue->size() - 2;
        while (j > -1 && obj->z() < RenderQueue->at(j)->z())
        {
            j--;
        }
        std::vector<Game_ObjectBase*>::iterator it = RenderQueue->begin();
        RenderQueue->insert(it + j, obj);
    }
    // other game objects
    for (int i = 0; i < _objects->size(); i++)
    {
        Game_ObjectBase* obj = _objects->at(i);
        if (obj->NeedRender() == false) {
            continue;
        }
        RenderQueue->push_back(obj);
        int j = RenderQueue->size() - 2;
        while (j > -1 && obj->z() < RenderQueue->at(j)->z())
        {
            j--;
        }
        std::vector<Game_ObjectBase*>::iterator it = RenderQueue->begin();
        RenderQueue->insert(it + j, obj);
    }
    // Render ingame objects
    for (int i = 0; i < RenderQueue->size(); i++)
    {
        RenderQueue->at(i)->Render();
    }
    // images

    // Render Images
}

void Scene_Battle::Update(DWORD dt)
{
    for (int i = 0; i < _objects->size(); i++)
    {
        Game_ObjectBase* obj = _objects->at(i);
        obj->Update(dt);
        obj->Update(dt, _objects);
    }
}