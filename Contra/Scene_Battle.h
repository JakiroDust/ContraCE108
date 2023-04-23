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
// DEMO
#include "Demo_Layer.h"
#include "Spatial.h"
using namespace std;


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
		// DEMO
		void Demo_Camera_Action();
	public:
		Scene_Battle() : Scene_Base(), _p1(make_unique< Game_Player>(40, 40, 2)) {  };
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

		void Create_Stage_Demo();


		/// from this is protype

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
	// Spawn an RedGunner
	void Execute_BasicSpawnerEvent();
};

