#pragma once

using namespace std;
#include "debug.h"

class Scene_Base
{
	protected:
		//vector<Game_Image*>* _images = NULL;
	public:
		// GET & SET
		// vector<Game_ObjectBase*>* objects() { return _objects; }

		// Run this function when scene start.
		virtual void Intro() {};
		// Run this function when scene delete.
		virtual void Outtro() {};
		// Key event handler
		virtual void KeyDownEventHandler(int KeyCode) {};
		// Key event handler
		virtual void KeyUpEventHandler(int KeyCode) {};

		virtual void Render() {}
		virtual void Update(DWORD dt) {}
};

