#pragma once

#include "Scene_Base.h"
#include "ScreenManager.h"
#include <string>
#include "debug.h"
#include "Game_Player.h"
#include "Game_Layer.h"
#include "Game_Blocker.h"
#include "Game_Terrain.h"
#include "Game_Collision.h"
#include "Game_Water.h"

#include "StageEventHandler_S1.h"

// DEMO
#include "Demo_Layer.h"
#include "Spatial.h"
#include "MusicManager.h"

#include "Utils.h"
#include "STL_storage.h"
using namespace std;
#define UP_BLOCK 1
#define DOWN_BLOCK -1
#define BRIDGE_BLOCK 2
#define NOTHING 999

#define Z_INDEX_PLAYER 5
#define Z_INDEX_ENEMY 4
#define Z_INDEX_BULLET 3
#define Z_INDEX_BACKGROUND 1
#define Z_INDEX_ANIMATION 6

class Scene_Battle : public Scene_Base
{
	private:
		int _p1_id=-1;
		int _p2_id=-1;
		unique_ptr< Game_Player> _p1 ;
		Game_Player* _p2 = NULL;
		vector<Game_Layer*> _layers;
		//vector<Game_ObjectBase*> _objects;
		unordered_map<int,unique_ptr<Game_ObjectBase>> __objects;
		int _mapWidth = 1;
		int _mapHeight = 1;
		void checkObjectNeedRender(Game_ObjectBase* obj);
		vector<int> getNearByIDyx(int y, int x);

		// Stage controller
		StageEventHandler_Base* _controller = NULL;

	public:
		Scene_Battle() : Scene_Base() {  }
		~Scene_Battle();
		//vector<Game_ObjectBase*>* objects() { return &_objects; }
		Game_Player* p1() { return dynamic_cast<Game_Player*>(__objects[_p1_id].get()); }
		void addPlayer1();
		Game_Player* p2() { return dynamic_cast<Game_Player*>(__objects[_p2_id].get()); }
		void addPlayer2();
		int MapWidth() { return _mapWidth; }
		int MapHeight() { return _mapHeight; }
		void SetMapSize(int width, int height) { _mapWidth = width; _mapHeight = height; }

		void Render() override;
		void Update(DWORD dt) override;
		void Load() override;
		void Unload() override;
		void Create_Stage_Demo();

		// Key event handler
		virtual void KeyDownEventHandler(int KeyCode) override {}

		/// from this is protype
		void SetStageEventHandler(StageEventHandler_Base* handler)
		{
			if (_controller != NULL)
				delete _controller;
			_controller = handler;
		}
		StageEventHandler_Base* GetStageEventHandler() { return _controller; }

	private:
		int id_nth = 0;
		vector<int> id_recycle_bin;
		void _init_spatial();
		void _delete_spatial();
	public:
		Spatial *spatial=NULL;
		vector<int> getNearByID(int n, int m);
		vector<int> getNearbyIDFast();
		vector<Game_ObjectBase*>* getObjectById(vector<int>& vtr);
		int add_object(unique_ptr<Game_ObjectBase>&& object);
		void delete_object(int id);
		//void delete_object(unique_ptr<Game_ObjectBase>& object);

		// from here is MAP SPATIAL
		void parseMap();

		///spatial map
	protected:
		unordered_map<int, unordered_map<int, int>> map;
		//unordered_map<int, int> map_info;
		unordered_map<int, unique_ptr<CSprite>> map_sprite;
		LPTEXTURE _map_tex=NULL;
		SpatialforTex* mapTexSpatial = NULL;
		void renderBG(float x, float y);
		void renderBG(int& x, int& y);
		int width, height, map_id;
	public:
		void _ParseSection_DICT(string line);
	
		void addMapPart( int partID, int x, int y);
};

