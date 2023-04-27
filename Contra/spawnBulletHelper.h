#pragma once
#include <unordered_map>
#include <vector>
#include "debug.h"
#include "Contra_GET_ANI.h"
#include "Enemies_ID.h"
#define DIR_TOP_LEFT 1
#define DIR_TOP 2
#define DIR_TOP_RIGHT 3
#define DIR_LEFT 4
#define DIR_RIGHT 6
#define DIR_BOTTOM_LEFT 7
#define DIR_BOTTOM 8
#define DIR_BOTTOM_RIGHT 9

#define X 0
#define Y 1
using namespace std;

#define CHAR_CONTRA_SIT 1099
class spawnBulletHelper
{
private:
   

    unordered_map<int,
    unordered_map<int, vector<float>> > _spawnBulletHelper;
    unordered_map<int, vector<float>> initHelper();
    spawnBulletHelper();
    static spawnBulletHelper* instance;
public:
    static spawnBulletHelper* getInstance() {
        if (instance == nullptr) {
            instance = new spawnBulletHelper();
        }
        return instance;
    }
    void getSpawnCor(float& x, float& y,int CHAR_ID, int& DIR)
    {
        x += _spawnBulletHelper[CHAR_ID][DIR][X];
        y += _spawnBulletHelper[CHAR_ID][DIR][Y];
    }

};

