#include "spawnBulletHelper.h"
spawnBulletHelper*  spawnBulletHelper::instance = nullptr;

unordered_map<int, vector<float>> spawnBulletHelper::initHelper()
{
    unordered_map<int, vector<float>> map;
    for (int i = 1; i <= 9; i++)
        map[i] = vector<float>(2, 0);
    map[DIR_TOP][X] = 0;
    map[DIR_TOP][Y] = 10;

    map[DIR_TOP_RIGHT][X] = 7;
    map[DIR_TOP_RIGHT][Y] = 7;

    map[DIR_RIGHT][X] = 10;
    map[DIR_RIGHT][Y] = 5;

    map[DIR_BOTTOM_RIGHT][X] = 7;
    map[DIR_BOTTOM_RIGHT][Y] = -7;

    map[DIR_BOTTOM][X] = 0;
    map[DIR_BOTTOM][Y] = -10;

    map[DIR_BOTTOM_LEFT][X] = -7;
    map[DIR_BOTTOM_LEFT][Y] = -7;

    map[DIR_LEFT][X] = -10;
    map[DIR_LEFT][Y] = 5;

    map[DIR_TOP_LEFT][X] = -7;
    map[DIR_TOP_LEFT][Y] = 7;
    return map;
}
spawnBulletHelper::spawnBulletHelper()
{
    _spawnBulletHelper[CHAR_CONTRA] = initHelper();
    _spawnBulletHelper[CHAR_CONTRA_SIT] = initHelper();
    _spawnBulletHelper[INFARY] = initHelper();
    _spawnBulletHelper[INFARY_BASE] = initHelper();
    _spawnBulletHelper[RED_GUNNER] = initHelper();
    _spawnBulletHelper[RED_GUNNER_BASE] = initHelper();
    _spawnBulletHelper[BLUE_GUNNER] = initHelper();
    _spawnBulletHelper[SNIPER] = initHelper();
    _spawnBulletHelper[SNEAKY_SNIPER] = initHelper();
    _spawnBulletHelper[SCUBA_DRIVER] = initHelper();
    _spawnBulletHelper[BOMB_TOSSER] = initHelper();
    _spawnBulletHelper[BOMB_TOSSER_BASE] = initHelper();
    _spawnBulletHelper[TURRET] = initHelper();
    _spawnBulletHelper[ELITE_TURRET] = initHelper();
    _spawnBulletHelper[TURRET_BASE] = initHelper();
    _spawnBulletHelper[ELITE_TURRET_BASE] = initHelper();
    _spawnBulletHelper[CANON] = initHelper();
    _spawnBulletHelper[Mine] = initHelper();
    _spawnBulletHelper[Mine_BASE] = initHelper();
    _spawnBulletHelper[FLY_DEF_ROBOT] = initHelper();
    _spawnBulletHelper[STAND_ROBOT] = initHelper();
    _spawnBulletHelper[MACHINE_GUNNER] = initHelper();
    _spawnBulletHelper[SHIELD_MACHINE_GUNNER] = initHelper();

}
