#pragma once

#include "KeyEventHandler.h"
#include "STL_storage.h"
#include "Texture.h"

#define UP_BLOCK 1
#define DOWN_BLOCK -1
#define BRIDGE_BLOCK 2
/*
*  Abstract class for a game scene
*/
class CScene
{
protected:
	LPKEYEVENTHANDLER key_handler;
	int id;
	LPCWSTR sceneFilePath;

public:
	
	CScene(int id, LPCWSTR filePath)
	{
		this->id = id;
		this->sceneFilePath = filePath;
		this->key_handler = NULL;
	}
	unordered_map<int, unordered_map<int, int>>& getMap();
	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 
	///spatial map
protected:
	unordered_map<int, unordered_map<int, int>> map;
	unordered_map<int, int> map_info;
	unordered_map<int, unique_ptr<CTexture>> map_tex;
public:
};
typedef CScene * LPSCENE;


class CSceneKeyHandler : public CKeyEventHandler
{
protected: 
	CScene * scence; 

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(LPSCENE s) :CKeyEventHandler() { scence = s; }
};

typedef CSceneKeyHandler* LPSCENEKEYHANDLER;