#include "Mapper.h"
#include "Game_Character.h"
#include "Game_Water.h"
#include "Game_Platform.h"
#include "Game_TestBox.h"

Mapper::Mapper(Game_Character* srcObj)
{
	_srcObj = srcObj;
}

PTERRAINNODE Mapper::GetHome()
{
	return _home;
}

void Mapper::UpdateMap(vector<Game_ObjectBase*>* coObjects)
{
	vector<Game_ObjectBase*>* filter = new vector<Game_ObjectBase*>();
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Game_Terrain*>(coObjects->at(i)))
		{
			filter->push_back(coObjects->at(i));
		}
	}

	if (_baseObjList.empty() || !Compare(filter))
	{
		_baseObjList.clear();
		for (int i = 0; i < filter->size(); i++)
		{
			_baseObjList.push_back(filter->at(i));
		}
		LinkingNode();
	}

	//------------------------------------------
	// Update home

	PTERRAINNODE home = GetDesNode(_srcObj);
	if (home != NULL)
		try
		{
			home->obj->id();
		}
		catch (...)
		{
			home = NULL;
		}
	_home = home;
	filter->clear();
	delete filter;
}

void Mapper::ClearMap()
{
	for (int i = 0; i < _map.size(); i++)
	{
		delete _map[i];
	}
	_map.clear();
}

bool firsttime = 0;

void Mapper::LinkingNode()
{
	float LINKUP_DIST_X = _dt * _srcObj->GetMovementSpeed() * 2;
	float LINKUP_DIST_Y = 40;
	float LINK_HORIZONAL = _dt * _srcObj->GetMovementSpeed() * _srcObj->GetJumpForce();

	// empty old map
	ClearMap();

	// init nodes
	
	for (int i = 0; i < _baseObjList.size(); i++)
	{
		PTERRAINNODE p = new TerrainNode();
		p->obj = ((Game_Terrain*)_baseObjList[i]);
		_map[p->obj->id()] = p;
		
		Game_Terrain* currentT = p->obj;

		// link nodes
		for (int j = 0; j < _baseObjList.size(); j++)
		{
			if (i == j)
				continue;
			Game_Terrain* selectedT = (Game_Terrain*)_baseObjList[j];

			// Check above node
			if (!dynamic_cast<Game_Water*>(currentT)
				&& (currentT->y() - selectedT->y()) > 1
				&& currentT->y() - selectedT->y() < LINKUP_DIST_Y
				&& ( (currentT->x() - LINKUP_DIST_X  >= selectedT->x()
					   && currentT->x() - LINKUP_DIST_X <= selectedT->x() + selectedT->width())
					|| (currentT->x() + currentT->width() + LINKUP_DIST_X >= selectedT->x()
						&& currentT->x() + currentT->width() + LINKUP_DIST_X <= selectedT->x() + selectedT->width())))
			{
				float length_y = selectedT->y() - currentT->y();
				float length_x = 0;
				if (currentT->x() + currentT->width() < selectedT->x())
				{
					length_x = selectedT->x() - (currentT->x() + currentT->width());
				}
				else if (currentT->x() > selectedT->x() + selectedT->width())
				{
					length_x = selectedT->x() + selectedT->width() - currentT->x();
				}
				p->nextNodes[selectedT->id()] = {length_x, length_y};
				continue;
			}
			// check side node
			if (
					// Current Node is normal terrain
					(
						!dynamic_cast<Game_Water*>(currentT)
						&& abs(currentT->y() - selectedT->y()) < 1
						&& (currentT->x() >= selectedT->x() - LINK_HORIZONAL
						&& currentT->x() + currentT->width() <= selectedT->x() - LINK_HORIZONAL)
					)
					||
					// Current Node is water terrain
					(
						dynamic_cast<Game_Water*>(currentT)
						&& (currentT->y() - selectedT->y()) < _srcObj->height() / 2
						&& (abs(currentT->x() + currentT->width() - selectedT->x()) < 0.5
							|| abs(selectedT->x() + selectedT->width() - currentT->x()) < 0.5)
					)
				)
			{
				float length_x = 0;
				if (currentT->x() + currentT->width() < selectedT->x())
				{
					length_x = selectedT->x() - (currentT->x() + currentT->width());
				}
				else if (currentT->x() > selectedT->x() + selectedT->width())
				{
					length_x = selectedT->x() + selectedT->width() - currentT->x();
				}
				float length_y = 0;
				p->nextNodes[selectedT->id()] = {length_x, length_y};
				continue;
			}
			// Check below node
			if (!dynamic_cast<Game_Water*>(currentT)
				&& (selectedT->y() - currentT->y()) > 1
				&& (selectedT->x() + selectedT->width() + LINK_HORIZONAL >= currentT->x()
					&& selectedT->x() - LINK_HORIZONAL <= currentT->x() + currentT->width()) 
			){
				float length_y = selectedT->y() - currentT->y();
				float length_x = 0;
				if (currentT->x() + currentT->width() < selectedT->x())
				{
					length_x = selectedT->x() - (currentT->x() + currentT->width());
				}
				else if (currentT->x() > selectedT->x() + selectedT->width())
				{
					length_x = selectedT->x() + selectedT->width() - currentT->x();
				}
				p->nextNodes[selectedT->id()] = {length_x, length_y};
				continue;
			}
		}
		//delete p;
	}

	firsttime = 1;
}

bool Mapper::Compare(vector<Game_ObjectBase*>* coObjects)
{
	if (coObjects->size() != _baseObjList.size())
	{
		return false;
	}
	for (int i = 0; i < coObjects->size(); i++)
	{
		bool result = false;
		for (int j = 0; j < _baseObjList.size(); j++)
		{
			if (_baseObjList[j] == coObjects->at(i))
			{
				result = true;
				break;
			}
		}
		if (!result)
			return false;
	}
	return true;
}

vector<PTERRAINNODE> Mapper::FindWay(Game_Character* des)
{
	// Detect target position
	PTERRAINNODE desNode = GetDesNode(des);

	// Path finding
	vector<PTERRAINNODE> path;

	if (_home == NULL)
	{
		return path;
	}

	if (desNode == NULL)
	{
		return path;
	}

	// Same terrain
	if (_home->obj == desNode->obj)
	{
		path.push_back(_home);
		return path;
	}

	// Draining Algorithm
	vector<PTERRAINNODE> result;
	unordered_map<int, bool> ignoreList;
	for (auto& i : _map)
	{
		ignoreList[i.first] = false;
	}
	vector<PTERRAINNODE> search = PathFinding_AStarAlgorithm(_home, desNode, ignoreList);

	for (int i = 0; i < search.size(); i++)
	{
		result.push_back(search[i]);
	}

	return result;
	// Implement shortest path-finding algorithm in the future
}

vector<PTERRAINNODE> Mapper::PathFinding_DrainingAlgorithm(PTERRAINNODE p, PTERRAINNODE &des, unordered_map<int, bool> &ignoreList)
{
	vector<PTERRAINNODE> search, result;
	ignoreList[p->obj->id()] = true;

	for (auto& i : p->nextNodes)
	{
		PTERRAINNODE next = _map[i.first];
		if (ignoreList[i.first] == true)
			continue;

		if (next == des)
		{
			result.push_back(p);
			result.push_back(des);
			return result;
		}

		search = PathFinding_DrainingAlgorithm(next, des, ignoreList);
		if (!search.empty())
		{
			result.push_back(p);
			for (int i = 0; i < search.size(); i++)
			{
				result.push_back(search[i]);
			}
			break;
		}
	}

	return result;
}

PTERRAINNODE Mapper::GetDesNode(Game_Character* des)
{
	PTERRAINNODE desNode = NULL;

	//Game_TestBox* testbox = new Game_TestBox(des->x(), des->y(), des->z(), des->width(), des->height(), 0, 0);
	//// Find which is Collision event


	for (int i = 0; i < _baseObjList.size(); i++)
	{
		Game_ObjectBase* terrain = _baseObjList[i];
		if (des->x() + des->width() > terrain->x()
			&& des->x() < terrain->x() + terrain->width()
			&& (terrain->y() - des->footerY()) > -1)
		{
			if (desNode == NULL || abs(terrain->y() - des->y()) < abs(desNode->obj->y() - des->y()))
			{
				desNode = _map[terrain->id()];
			}
		}
	}
	return desNode;
}

vector<PTERRAINNODE> Mapper::PathFinding_AStarAlgorithm(PTERRAINNODE p, PTERRAINNODE& des, unordered_map<int, bool>& ignoreList)
{
	vector<AStarNode> Open, Close;

	AStarNode startNode;
	startNode.TNode = p;
	startNode.Update_H_value(des->obj);
	startNode.G = 0;
	startNode.path.push_back(startNode.TNode->obj->id());
	Open.push_back(startNode);
	ignoreList[p->obj->id()] = true;

	do
	{
		// Get Lowest-G Node

		AStarNode S;
		int index = -1;
		for (int i = 0; i < Open.size(); i++)
		{
			if (index == -1 || Open[i].G + Open[i].H < S.G + S.H)
			{
				S = Open[i];
				index = i;
			}
		}

		// Can't find a path
		if (Open.empty())
		{
			Close.clear();
			break;
		}

		// Checking all next nodes of S
		int hit = 0;
		for (auto& next : S.TNode->nextNodes)
		{


			PTERRAINNODE nextTP = _map[next.first];
			if (ignoreList[next.first] == true)
				continue;

			//ignoreList[nextTP->obj->id()] = true;
			AStarNode ASNode;
			ASNode.TNode = nextTP;
			ASNode.Update_H_value(des->obj);
			ASNode.G = abs(next.second.first) + abs(next.second.second) + S.G;
			bool isExist = false;
			for (auto &check : Open)
			{
				if (check.TNode == ASNode.TNode)
				{
					if (ASNode.Cost() < check.Cost())
					{
						check.G = ASNode.G;
						check.H = ASNode.H;
						// update path
						check.path.clear();
						for (int i = 0; i < ASNode.path.size(); i++)
						{
							check.path.push_back(ASNode.path[i]);
						}
					}
					isExist = true;
					break;
				}
			}
			hit++;
			if (isExist)
				continue;
			for (int i = 0; i < S.path.size(); i++)
			{
				ASNode.path.push_back(S.path[i]);
			}
			ASNode.path.push_back(ASNode.TNode->obj->id());
			Open.push_back(ASNode);
		}

		std::vector<AStarNode>::iterator it = Open.begin();
		// Ignore Dead node
		if (S.TNode != des && hit == 0)
		{
			Open.erase(it + index);
			ignoreList[S.TNode->obj->id()] = true;
			continue;
		}

		// Add to Close
		Close.push_back(S);
		ignoreList[S.TNode->obj->id()] = true;
		Open.erase(it + index);

	} while (Close.size() > 0 && Close[Close.size() - 1].TNode != des);
	
	vector<PTERRAINNODE> result;
	if (Close.empty())
	{
		return result;
	}

	AStarNode FinalPath = Close[Close.size() - 1];

	for (int i = 0; i < FinalPath.path.size(); i++)
	{
		result.push_back(_map[FinalPath.path[i]]);
	}
	return result;
}

void AStarNode::Update_H_value(Game_ObjectBase* des)
{
	if (TNode == NULL)
		return;
	Game_Terrain* currentT = TNode->obj;
	float length_y = des->y() - currentT->y();
	float length_x = 0;
	if (currentT->x() + currentT->width() < des->x())
	{
		length_x = des->x() - (currentT->x() + currentT->width());
	}
	else if (currentT->x() > des->x() + des->width())
	{
		length_x = des->x() + des->width() - currentT->x();
	}
	H = abs(length_x) + abs(length_y);
}