#pragma once
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


enum TURRET_DIR
{
 DIR_1_OCLOCK=10,
 DIR_2_OCLOCK,
 DIR_3_OCLOCK,
 DIR_4_OCLOCK,
 DIR_5_OCLOCK,
 DIR_6_OCLOCK,
 DIR_7_OCLOCK,
 DIR_8_OCLOCK,
 DIR_9_OCLOCK,
 DIR_10_OCLOCK,
 DIR_11_OCLOCK,
 DIR_12_OCLOCK,
 DIR_OCLOCK

};
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

    void initTurret(unordered_map<int, vector<float>>& map);

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
namespace BULLETHELPER
{
    void getSpawnCor(float& x, float& y, int CHAR_ID, int state, int& DIR);
}
