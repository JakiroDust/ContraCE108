#pragma once

#include "string"
#include "debug.h"
#include "Game_Terrain.h"

using namespace std;

// This class is used by Game_Enemy, create a map for them to make decision what to do next.
// (Ex: Find the way to chase player)
class Game_Character;

struct TerrainNode
{
	Game_Terrain* obj = NULL;

	unordered_map<int, pair<float,float>> nextNodes;

};
typedef TerrainNode* PTERRAINNODE;

struct AStarNode
{
	PTERRAINNODE TNode;
	float G;
	float H;
	vector<int> path;
	void Update_H_value(Game_ObjectBase* des);
	float Cost() { return G + H; }
};

class Mapper
{
	private:
		unordered_map<int, PTERRAINNODE> _map;
		PTERRAINNODE _home;
		vector<Game_ObjectBase*> _baseObjList;

		DWORD _dt;
		Game_Character* _srcObj;
		void ClearMap();
		bool Compare(vector<Game_ObjectBase*>* coObject);
		void LinkingNode();

		vector<PTERRAINNODE> PathFinding_DrainingAlgorithm(PTERRAINNODE p, PTERRAINNODE& des, unordered_map<int, bool> &ignoreList);
		vector<PTERRAINNODE> PathFinding_AStarAlgorithm(PTERRAINNODE p, PTERRAINNODE& des, unordered_map<int, bool>& ignoreList);
	public:
		Mapper(Game_Character* srcObj);
		void UpdateMap(vector<Game_ObjectBase*>* coObjects);
		void SetDt(DWORD dt) { _dt = dt; }
		PTERRAINNODE GetHome();
		vector<PTERRAINNODE> FindWay(Game_Character* des);
		PTERRAINNODE GetDesNode(Game_Character* des);

};
 

